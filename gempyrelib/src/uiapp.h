#ifndef PYTHON_H
#define PYTHON_H

#include "semaphore.h"

namespace Gempyre {

class UiApp {
public:
    UiApp();
    bool isStarted();
    ~UiApp();
private:
    int m_error{0};
    std::thread m_thread;
    Gempyre::Semaphore m_sema;
};
}

#endif // PYTHON_H
