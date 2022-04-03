#ifdef __APPLE__
#include <Python/Python.h>
#else
#include <Python.h>
#endif
class PythonScripts {
    private:
        PyObject *uartModule;
        PyObject *httpModule;
    public:
        int init();
        PyObject* loadModule(const char *name);
    
        int readUART();

        void sendData();
};
