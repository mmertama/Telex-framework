#include <thread>

#if HAS_PYTHON
//extern "C" {
#undef _DEBUG
#include "Python.h"
//}
#endif

#include "uiapp.h"
#include "gempyre_utils.h"
#include "base64.h"
#include "generated/uiapp_python.h"



using namespace Gempyre;

UiApp::UiApp() : m_thread([this]() {
#if HAS_PYTHON
    {
    wchar_t *program = Py_DecodeLocale("_gempyre_", nullptr);
    if (program == NULL) {
        GempyreUtils::log(GempyreUtils::LogLevel::Error, "Cannot load Python");
        m_error = 1;
        return;
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();

    const auto app_py = Base64::decode(Pyclientpy);

    m_sema.signal();
    const auto data = const_cast<char*>(reinterpret_cast<const char*>(app_py.data()));

    PyRun_SimpleString(data);
    if (Py_FinalizeEx() < 0) {
        m_error = 2;
    }
    PyMem_RawFree(program);
    }
#else
        m_error = -1;
#endif
    m_sema.signal();
}) {
    m_sema.wait();
}

bool UiApp::isStarted() {
    m_sema.wait();
    return m_error == 0;
}

UiApp::~UiApp() {
    m_thread.join();
}
