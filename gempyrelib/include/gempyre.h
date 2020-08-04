#ifndef GEMPYRE_H
#define GEMPYRE_H

#include <iterator>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <deque>
#include <chrono>
#include <atomic>
#include <any>
#include <optional>
#include <vector>
#include <variant>
#include <mutex>

/**
  * ![wqe](https://avatars1.githubusercontent.com/u/7837709?s=400&v=4)
  *
  * gempyre.h
  * =====
  * Gempyre GUI Framework
  * -------------
  *
  * gempyre.h contains core functionality, everything that is needed for basic application using Gempyre framework.
  *
  * There are two classes: The Ui creates a Ui framework, and Element represents visual on screen. Basically flow is
  * create Ui -> intialize elements -> start event loop. There are several type of constructor - Ui::Filemap are using
  * compile time encoded files. File are added using `addResource` CMake function:
  * ```
  * addResource(
  * PROJECT <PROJECT_NAME>
  * TARGET <GENERATED_HEADER>
  * SOURCES <LIST-OF-ENCODED_FILES>)
  * ```
  * a simple main goes as follows:
  *
  * ```
  * int main() {
  *     Gempyre::Ui ui({{"/index.html", Tickhtml}}, "index.html");
  *     Gempyre::Element header(ui, "header");
  *      ui.startTimer(10000ms, true, [header]() mutable {
  *         header.setHTML("time force");
  *     });
  *      ui.run();
  * }
  *  ```
  * Please note that UI is not created until event loop is running,
  * that means any Ui query is not possible before event loop is running.
  * To resolve issue there is onOpen callback that is called immediately
  * after event loop has been started.
  *
  * @toc
  *
  */

using namespace std::chrono_literals;

#ifdef WINDOWS_EXPORT
#define GEMPYRE_EX __declspec( dllexport )
#else
#define GEMPYRE_EX
#endif

/**
 * @namespace Gempyre
 * Common namespace for Gempyre implementation.
 */
namespace Gempyre {

    class Ui;
    class Server;
    class Semaphore;
    class TimerMgr;
    template <class T> class EventQueue;
    template <class T> class IdList;
    template <class K, class T> class EventMap;

    enum class DebugLevel{None, Fatal, Error, Warning, Info, Debug, Debug_Trace};
    /**
     * @function setDebug
     * Enable debug outputs
     */
    GEMPYRE_EX void setDebug(DebugLevel level = DebugLevel::Debug);

#ifdef ANDROID_OS
    GEMPYRE_EX void setJNIENV(void* env, void* obj);
#endif

    /**
     * @function version
     */
    GEMPYRE_EX std::tuple<int, int, int> version();

    class Data;
    using DataPtr = std::shared_ptr<Data>;
    class GEMPYRE_EX Data {
    public:
        template <class T> class iteratorT {
        public:
            using iterator_category = std::forward_iterator_tag; //could be upgraded, but I assume there is no need
            using value_type = T;
            using difference_type = void;
            using pointer = T*;
            using reference = T&;
            iteratorT(pointer data = nullptr) : m_data(data) {}
            iteratorT(const iteratorT& other) = default;
            iteratorT& operator=(const iteratorT& other) = default;
            bool operator==(const iteratorT& other) const  {return m_data == other.m_data;}
            bool operator!=(const iteratorT& other) const  {return m_data != other.m_data;}
            reference operator*() {return *m_data;}
            reference operator*() const {return *m_data;}
            pointer operator->() {return m_data;}
            value_type operator++() {++m_data ; return *m_data;}
            value_type operator++(int) {auto temp(m_data); ++m_data; return *temp;}
        private:
            pointer m_data;
        };
        using dataT = uint32_t;
        using iterator = iteratorT<dataT>;
        using const_iterator = iteratorT<const dataT>;
    public:
        dataT* data();
        const dataT* data() const;
        size_t size() const;
        Data::iterator begin() {return data();}
        Data::iterator end() {return data() + size();}
        const Data::const_iterator begin() const {return data();}
        const Data::const_iterator end() const {return data() + size();}
        dataT& operator[](int index) {return (data()[index]);}
        dataT operator[](int index) const {return (data()[index]);}
        dataT* endPtr() {return data() + size();}
        const dataT* endPtr() const {return data() + size();}
        void writeHeader(const std::vector<dataT>& header);
        std::vector<dataT> header() const;
        std::string owner() const;
        DataPtr clone() const;
        virtual ~Data() = default;
    protected:
        Data(size_t sz, dataT type, const std::string& owner, const std::vector<dataT>& header);
    private:
        std::tuple<const char*, size_t> payload() const;
        std::vector<dataT> m_data;
        friend class Element;
        friend class Ui;
    };

    struct Event;

    /**
     * @class Element
     * Element represents any UI element
     */
    class GEMPYRE_EX Element {
    public:
        using Attributes = std::unordered_map<std::string, std::string>;
        using Values = std::unordered_map<std::string, std::string>;
        using Elements = std::vector<Element>;
        /**
         * @class The Rect
         */
        struct Rect {
            /**
             * @brief x
             */
            int x;
            /**
             * @brief y
             */
            int y;
            /**
             * @brief width
             */
            int width;
            /**
             * @brief height
             */
            int height;
        };
    public:
        Element(const Element& other) = default;
        Element(Element&& other) = default;
        Element& operator=(const Element& other) {m_ui = other.m_ui; m_id = other.m_id; return *this;}
        Element& operator=(Element&& other) {m_ui = other.m_ui; m_id = std::move(other.m_id); return *this;}
        /**
         * @function Element
         * @param ui
         * @param id
         *
         * Creates instance that refers to existing element.
         */
        Element(Ui& ui, const std::string& id);
        /**
         * @function Element
         * @param ui
         * @param id
         * @param htmlElement
         * @param parent
         *
         * Creates a new elements as given HTML type and parent.
         */
        Element(Ui& ui, const std::string& id, const std::string& htmlElement, const Element& parent);

        /**
         * @function Element
         * @param ui
         * @param htmlElement
         * @param parent
         *
         * Creates a new elements as given HTML type and parent.
         */
        Element(Ui& ui, const std::string& htmlElement, const Element& parent);

        virtual ~Element() = default;
        /**
         * @function ui
         * @return Ui
         *
         * Return current Ui.
         */
        const Ui& ui() const {
            return *m_ui;
        }
        /**
         * @function ui
         * @return Ui
         *
         * Return current Ui.
         */
        Ui& ui() {
            return *m_ui;
        }
        /**
         * @function id
         * @return string
         *
         * HTML identifer of this element
         */
        std::string id() const {return m_id;}
        /**
         * @function subscribe
         * @param name
         * @param handler
         * @param properties
         * @param throttle
         * @return Element
         *
         * Set a function to listen ui event.
         */
        Element& subscribe(const std::string& name, std::function<void(const Event& ev)> handler, const std::vector<std::string>& properties = {}, const std::chrono::milliseconds& throttle = 0ms);
        /**
         * @function setHTML
         * @param name
         * @param handler
         * @return Element
         *
         * Set HTML content for element.
         */
        Element& setHTML(const std::string& htmlText);
        /**
         * @function setAttribute
         * @param attr
         * @param value
         * @return Element
         *
         * Set a given attribute a given name
         */
        Element& setAttribute(const std::string& attr, const std::string& value = "");
        /**
         * @function attributes
         * @return optional Attributes
         *
         * Return Attributes.
         */
        std::optional<Attributes> attributes() const;
        /**
         * @function setStyle
         * @param style
         * @param value
         * @return Element
         */
        Element& setStyle(const std::string& style, const std::string& value);
        /**
         * @function removeStyle
         * @param style
         * @return Element
         */
        Element& removeStyle(const std::string& style);
        /**
         * @function removeAttribute
         * @param attr
         * @return Element
         */
        Element& removeAttribute(const std::string& attr);
        /**
         * @brief styles
         * @param keys
         * @return
         */
        std::optional<Values> styles(const std::vector<std::string>& keys) const;
        /**
         * @function children
         * @return optional Elements
         *
         * Return child elements (only direct children).
         */
        std::optional<Elements> children() const;
        /**
         * @function values
         * @return optional Values
         *
         * Return values. (e.g. input values).
         */
        std::optional<Values> values() const;
        /**
         * @function html
         * @return optional string
         *
         * Return html content of this element.
         */
        std::optional<std::string> html() const;
        /**
         * @function remove
         *
         * Remove this element from Ui.
         */
        void remove();
        /**
         * @function type
         * @return optiona string.
         *
         * Return type as HTML tag in lower case, empty is not found.
         */
        std::optional<std::string> type() const;
        /**
         * @function rect
         * @return optional Rect
         *
         * Return bounding rect of element
         */
        std::optional<Rect> rect() const;
    protected:
        void send(const DataPtr& data);
        void send(const std::string& type, const std::any& data);
        static const std::string generateId(const std::string& prefix);
    protected:
        Ui* m_ui;
        std::string m_id;
        friend class Ui;
    };
    struct Event {
        Element element;
        std::unordered_map<std::string, std::string> properties;
    };
    /**
     * @scopeend
     */

     /**
      * @class Ui
     */
    class GEMPYRE_EX Ui {
        struct Event {
            Element element;
            const std::unordered_map<std::string, std::any> properties;
        };
        using Handler = std::function<void(const Event& el)>;
    public:
        using Filemap = std::unordered_map<std::string, std::string>;
        using TimerId = int;
        static constexpr unsigned short UseDefaultPort = 0; //zero means default port
        static constexpr char UseDefaultRoot[] = "";   //zero means default root
        /**
         * @function Ui
         * @param indexHtml
         * @param browser
         * @param extraParams
         * @param port, has default
         * @param root, has default
         *
         * Constructor
         */
        explicit Ui(const std::string& indexHtml, const std::string& browser, const std::string& extraParams = "", unsigned short port = UseDefaultPort, const std::string& root = UseDefaultRoot);
        /**
         * @function Ui
         * @param indexHtml
         * @param port, has default
         * @param root, has default
         *
         * Constructor
         */
        explicit Ui(const std::string& indexHtml, unsigned short port = UseDefaultPort, const std::string& root = UseDefaultRoot);
        /**
         * @function Ui
         * @param filemap
         * @param indexHtml
         * @param browser
         * @param extraParams, has defaul
         * @param port, has default
         * @param root, has default
         *
         * Constructor
         */
        explicit Ui(const Filemap& filemap, const std::string& indexHtml, const std::string& browser, const std::string& extraParams = "", unsigned short port = UseDefaultPort, const std::string& root = UseDefaultRoot);
        /**
         * @function Ui
         * @param filemap
         * @param indexHtml
         * @param port, has default
         * @param root, has default
         *
         * Constructor
         */
        explicit Ui(const Filemap& filemap, const std::string& indexHtml, unsigned short port = UseDefaultPort, const std::string& root = UseDefaultRoot);
        ~Ui();
        Ui(const Ui& other) = delete;
        Ui(Ui&& other) = delete;
        /**
         * @function exit
         *
         * Exits the eventloop and make application to close.
         */
        void exit();
        /**
         * @function close
         *
         * Asks Client window to close (which then signals application to close)
         */
        void close();
        /**
         * @function onExit
         * @param onExitFunction
         * @return Ui
         *
         * Callback just before exit.
         */
        Ui& onExit(std::function<void ()> onExitFunction = nullptr);
        /**
         * @function onReload
         * @param onReleadFunction
         * @return Ui
         *
         * Callback when browser window reload occurs.
         */
        Ui& onReload(std::function<void ()> onReleadFunction = nullptr);
        /**
         * @function onOpen
         * @param onOpenFunction
         * @return Ui
         *
         * Callback when browser UI is running.
         */
        Ui& onOpen(std::function<void ()> onOpenFunction = nullptr);
        /**
         * @function onError
         * @param onErrorFunction
         * @return Ui
         *
         * Browser reports an issue
         */
        Ui& onError(std::function<void (const std::string& element, const std::string& info)> onErrorFunction = nullptr);
        /**
         * @function run
         *
         * Starts eventloop
         */
        void run();
        /**
         * @function setLogging
         * @param logging
         *
         * Enforces Browser being verbose when serving Gempyre.
         */
        void setLogging(bool logging);
        /**
         * @function eval
         * @param eval
         *
         * Execute code on browser (calls JS eval)
         */
        void eval(const std::string& eval);
        /**
         * @function debug
         * @param msg
         *
         * Echoes a message
         */
        void debug(const std::string& msg);
        /**
         * @function alert
         * @param msg
         *
         * Shown a browser's alert dialogue
         */
        void alert(const std::string& msg);
        /**
         * @function open
         * @param url
         * @param name
         *
         * Opens an extrenal URL on browser tab
         */
        void open(const std::string& url, const std::string& name = "");
        /**
         * @function startTimer
         * @param ms
         * @param singleShot
         * @param timerFunc
         * @return TimerId
         *
         * Starts a timer that is called after given amount of milliseconds.
         */
        TimerId startTimer(const std::chrono::milliseconds& ms, bool singleShot, const std::function<void (TimerId id)>& timerFunc);
        /**
         * @function startTimer
         * @param ms
         * @param singleShot
         * @param timerFunc
         * @return TimerId
         *
         * Starts a timer that is called after given amount of milliseconds.
         */
        TimerId startTimer(const std::chrono::milliseconds& ms, bool singleShot, const std::function<void ()>& timerFunc);
        /**
         * @function stopTimer
         * @return Boolean
         *
         * Stop the timer.
         */
        bool stopTimer(TimerId);
        /**
         * @function root
         * @return Element
         *
         * Pseudo element that represents root of the element structure
         */
        Element root() const;
        /**
         * @function addressOf
         * @param filepath
         * @return string
         *
         * Translates given path to address that Gempyre can read when provided as a link.
         */
        std::string addressOf(const std::string& filepath) const;
        /**
         * @function byClass
         * @param className
         * @return optional list of Elements
         *
         * Returns all elements match to given class
         */
        std::optional<Element::Elements> byClass(const std::string& className) const;
        /**
         * @function byName
         * @param className
         * @return optional list of Elements.
         *
         * Returns all elements match to given name
         */
        std::optional<Element::Elements> byName(const std::string& className) const;
        /**
         * @function ping
         * @return optional pair of times.
         *
         * Just a ping.
         */
        std::optional<std::pair<std::chrono::microseconds, std::chrono::microseconds>> ping() const;
        /**
         * @function extension
         * @param callId
         * @param parameters
         * @return optional any
         *
         * Low level access to extension services that browser may implement. The return parameter and return value are JSON kind
         * of structures or types and depends on given callId.
         * Note if return value contain a string it is very straighforward
         *
         * for example
         *```
         * const auto out = ui.extension("openFile", {{"caption", "hexview - open"}});
         * const std::string filename = std::any_cast<std::string>(*out);
         *```
         * but if is an array of string values must be converted accordint to structure
         *```
         * const auto out = ui.extension("openFile", {{"caption", "hexview - open"}});
         * const auto anyvec = std::any_cast<std::vector<std::any>(*out);
         * std::vector<std::string> vec;
         * std::transform(anyvec.begin(), anyvec.end, std::back_inserter(vec), [](const auto& a){return std::any_cast<std::string>(a)});
         *```
         */
        std::optional<std::any> extension(const std::string& callId, const std::unordered_map<std::string, std::any>& parameters);

        /**
         * @function resource
         * @param url
         * @return optional byte vector
         *
         * Get data stored as a resource
         */
        std::optional<std::vector<uint8_t>> resource(const std::string& url) const;
        /**
         * @function addFile
         * @param url
         * @param file
         * @return boolean
         *
         * Adds a file as a resources
         */
        bool addFile(const std::string& url, const std::string& file);
        /**
         * @function beginBatch
         *
         * Starts buffering non-DataPtr message locally
         */
        void beginBatch();
        /**
         * @function endBatch
         *
         * Sends locally buffered message to UI
         */
        void endBatch();
        /**
         * @function holdTimers
         * @param hold
         */
        void holdTimers(bool hold) {m_hold = hold;}
        /**
         * @function isHold
         * @return
         */
        bool isHold() const {return m_hold;}
    private:
        enum class State {NOTSTARTED, RUNNING, RETRY, EXIT, CLOSE, RELOAD, PENDING};
        void send(const DataPtr& data);
        void send(const Element& el, const std::string& type, const std::any& data);
        template<class T> std::optional<T> query(const std::string& elId, const std::string& queryString, const std::vector<std::string>& queryParams = {});
        void pendingClose();
        void eventLoop();
        static std::string toStr(const std::atomic<State>&);
        inline void addRequest(std::function<bool()>&&);
    private:
        std::atomic<State> m_status = State::NOTSTARTED;
        std::unique_ptr<EventQueue<std::tuple<std::string, std::string, std::unordered_map<std::string, std::any>>>> m_eventqueue;
        std::unique_ptr<EventMap<std::string, std::any>> m_responsemap;
        std::unique_ptr<Semaphore>  m_sema;
        std::unique_ptr<TimerMgr> m_timers;
        using HandlerMap = std::unordered_map<std::string, Handler>;
        std::unordered_map<std::string, HandlerMap> m_elements;
        std::deque<std::function<bool ()>> m_requestqueue;
        std::deque<std::function<void ()>> m_timerqueue;
        std::function<void ()> m_onUiExit = nullptr;
        std::function<void ()> m_onReload = nullptr;
        std::function<void ()> m_onOpen = nullptr;
        std::function<void (const std::string& element, const std::string& info)> m_onError = nullptr;
        std::unique_ptr<Server> m_server;
        std::function<void ()> m_startup;
        Filemap m_filemap;
        std::mutex m_mutex;
        bool m_hold = false;
        friend class Element;
        friend class Server;
    };
    /**
     * @scopeend
     */
}
/**
 * @scopeend
 */

#endif // GEMPYRE_H
