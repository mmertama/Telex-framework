#include "timer.h"


using namespace Gempyre;

class Gempyre::TimeQueue {
public:
    using TimeType = TimerMgr::TimeType;
    using Function = TimerMgr::Function;
    struct Data {
        Data(const Data& other) = default;
        Data(Data&& other) = default;

        Data(const TimeType& t, const Function& f, const TimeType& i, int d) :
            currentTime(t), func(f), initialTime(i), id(d) {}
        TimeType currentTime = std::chrono::milliseconds(0); //when this is 0 the timer elapses
        Function func = nullptr;                             //function to run
        TimeType initialTime = std::chrono::milliseconds(0); //requested time, for recurring timer
        int id = 0;                                          //id of this timer
    //    bool blessed = true;
        char _PADDING[4] =  "\0\0\0";                        //compiler warnings
    };
    using DataPtr = std::shared_ptr<Data>;
private:
    struct Comp {
    bool operator()(const DataPtr& a, const DataPtr& b) const {
            return a->currentTime > b->currentTime;
        };
    };
public:
    TimeQueue() {
    }

    int append(const TimeType& ms, const Function& func) {
        std::lock_guard<std::mutex> guard(m_mutex);
        ++m_id; //just a running number
        m_priorityQueue.insert(std::make_shared<Data>(ms, func, ms, m_id));  //priorize                                         //set this timer to timer set
        return m_id;
    }

    bool restoreIf(int id) {
        std::lock_guard<std::mutex> guard(m_mutex);
        auto it = std::find_if(m_priorityQueue.begin(), m_priorityQueue.end(), [&id](const auto& d){return d->id == id;});
        if(it == m_priorityQueue.end())
            return false;
 //       assert(!(*it)->blessed);
        auto data = m_priorityQueue.extract(it);
//        data.value()->blessed = true;
        data.value()->currentTime = data.value()->initialTime;
        m_priorityQueue.insert(std::move(data));  //priorize
        return true;
    }

    void reduce(const TimeType& sleep) {
        std::lock_guard<std::mutex> guard(m_mutex);
        for(auto& d : m_priorityQueue) {
            d->currentTime -= sleep;
        }
    }


/*    void bless(int id) {
        std::lock_guard<std::mutex> guard(m_mutex);
        auto it = std::find_if(m_priorityQueue.begin(), m_priorityQueue.end(), [&id](const auto& d){return d->id == id;});
        assert(it != m_priorityQueue.end());
        assert(!(*it)->blessed);
        (*it)->blessed = true;
    }

    [[nodiscard]]
    bool blessed(int id) const {
        std::lock_guard<std::mutex> guard(m_mutex);
        auto it = std::find_if(m_priorityQueue.begin(), m_priorityQueue.end(), [&id](const auto& d){return d->id == id;});
        assert(it != m_priorityQueue.end());
        return it != m_priorityQueue.end() && (*it)->blessed;
    }

    void takeBless(int id) {                                    //remove from set, if found
        std::lock_guard<std::mutex> guard(m_mutex);
        auto it = std::find_if(m_priorityQueue.begin(), m_priorityQueue.end(), [&id](const auto& d){return d->id == id;});
        assert(it != m_priorityQueue.end());
        assert((*it)->blessed);
        (*it)->blessed = false;
    }
*/
    void remove(int id) {                                      //Remove a timer
        std::lock_guard<std::mutex> guard(m_mutex);
        auto it = std::find_if(m_priorityQueue.begin(), m_priorityQueue.end(), [&id](const auto& d){return d->id == id;});
        assert(it != m_priorityQueue.end());
        m_priorityQueue.erase(it);
    }

    bool contains(int id) const {
        std::lock_guard<std::mutex> guard(m_mutex);
        const auto it = std::find_if(m_priorityQueue.begin(), m_priorityQueue.end(), [&id](const auto& d){return d->id == id;});
        return it != m_priorityQueue.end();
    }

    /// Change everything executed now
    /// keepBless = false, not executed set, has to be blessed
    void setNow(/*bool keepBless = true*/) {
        std::lock_guard<std::mutex> guard(m_mutex);
    //    std::vector<Data> store;
        for(auto& c : m_priorityQueue) {
    /*        if(!keepBless) {
               c->blessed = false;
            }*/
            c->currentTime = std::chrono::milliseconds{0};
        }
    }


    //peek the next item
    [[nodiscard]]
    std::optional<Data> copyFirstBlessed() const {
        GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer queue peek", m_priorityQueue.size());
        std::unique_lock<std::mutex> guard(m_mutex);
        const auto it = m_priorityQueue.begin();
        if(it != m_priorityQueue.end()) {
            const auto value = std::make_optional(*(*it));
            guard.unlock(); // I have no idea why RAII wont work, unlock does
            GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer queue return");
            return value;
        /* for(const auto& d : m_priorityQueue) {
            if(d->blessed) {
                const auto value = std::make_optional(*d);
                guard.unlock(); // I have no idea why RAII wont work, unlock does
                GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer queue return");
                return value;
            }*/
        }
        GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer queue is empty");
        return std::nullopt;
    }

    void clear() {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_priorityQueue.clear();
    }

    [[nodiscard]]
    bool empty() const {
        std::lock_guard<std::mutex> guard(m_mutex);
        return m_priorityQueue.empty();
    }

    [[nodiscard]]
    size_t size() const {
        std::lock_guard<std::mutex> guard(m_mutex);
        return m_priorityQueue.size();
    }


private:
    static Comp m_comp;
    mutable std::mutex m_mutex;
    //std::priority_queue<Data, std::vector<Data>, Comp> m_queue;
    int m_id = 0;
    //std::set<int> m_blessed;
    std::multiset<DataPtr, Comp> m_priorityQueue;
};


void TimerMgr::start() {
    m_exit = false;
    m_timerThread = std::async([this]() {
        GempyreUtils::log(GempyreUtils::LogLevel::Debug, "timer thread start");
        for(;;) {
            GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer thread loop");
            const auto itemOr = m_queue->copyFirstBlessed();
            GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer queue peeked");
            if(!itemOr.has_value()) {
                GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer thread loop exit");
                break; //empty
            }
            GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer thread has value");
            const auto data = itemOr.value(); //value is shared pointer thus is floats even killed, and we wait
            const auto currentSleep = data.currentTime;
            GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer thread wait", currentSleep.count());
            if(currentSleep > std::chrono::milliseconds{0}) {
                GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer thread lock active");
                std::unique_lock<std::mutex> lock(m_waitMutex);
                const auto begin = std::chrono::steady_clock::now();
                GempyreUtils::log(GempyreUtils::LogLevel::Debug, "timer wait now:", data.id);
                m_cv.wait_for(lock, std::chrono::duration(currentSleep));
                const auto end = std::chrono::steady_clock::now(); //we may have had an early  wakeup
                const auto actualWait = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
                GempyreUtils::log(GempyreUtils::LogLevel::Debug, "timer awake id:", data.id , currentSleep.count(), actualWait.count(), m_queue->size());
                m_queue->reduce(actualWait);  //so we see if we are still there, and restart
                continue; // we have slept
            }
            GempyreUtils::log(GempyreUtils::LogLevel::Debug, "timer pop id:", data.id, m_queue->size());
      //      m_queue->pop();
            GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer thread function");
            data.func(data.id);
            if(!m_exit) {
                GempyreUtils::log(GempyreUtils::LogLevel::Debug_Trace, "timer thread reappend");
                m_queue->restoreIf(data.id); //restart it
            } else {
                 GempyreUtils::log(GempyreUtils::LogLevel::Debug, "timer exit on, id:", data.id, m_queue->size());
            }
        }
        GempyreUtils::log(GempyreUtils::LogLevel::Debug, "timer thread ended", m_queue->size());
    });
}

int TimerMgr::append(const TimeQueue::TimeType& ms, bool singleShot, const TimeQueue::Function& timerFunc, const Callback& cb) {
    const auto doStart = m_queue->empty();
    const auto id = m_queue->append(ms, [singleShot, timerFunc, this, cb] (int id) {
        const auto f = [singleShot, timerFunc, id, this]() {
            {
          //      m_queue->takeBless(id);
                GempyreUtils::log(GempyreUtils::LogLevel::Debug, "Timer running", id);
                timerFunc(id);
                if(singleShot)   {
                    GempyreUtils::log(GempyreUtils::LogLevel::Debug, "Timer", id, "decided to finish");
                    remove(id);
                } else {
                    GempyreUtils::log(GempyreUtils::LogLevel::Debug, "Timer bless", id);
                //    m_queue->bless(id);
                }
            }
        };
        cb(f);
    });

    GempyreUtils::log(GempyreUtils::LogLevel::Debug, "timer append", id, m_queue->size());

    if(doStart) {
        start();
    }
    m_cv.notify_all(); //if appeded thread is done, priot que may have changed
    return id;
}


bool TimerMgr::remove(int id) {
    if(m_queue->empty())
        return false;
    m_queue->remove(id);
    m_cv.notify_all();  //if currently waiting has been waiting thing may have changed
    return true;
}

void TimerMgr::flush(bool /*doRun*/) {
    if(!m_queue->empty()) {
        GempyreUtils::log(GempyreUtils::LogLevel::Debug, "flush");
        m_queue->setNow(); //There was a feature that on flush (on exit) all timers are run.
        m_exit = true;
        m_cv.notify_all();
        m_timerThread.wait();
    }
}

TimerMgr::~TimerMgr() {
    if(!m_queue->empty()) {
        m_queue->clear();
        m_cv.notify_all();
        m_timerThread.wait();
    }
}

TimerMgr::TimerMgr() : m_queue(std::make_unique<TimeQueue>()) {
}

