#include <Python/Python.h>


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
