#ifdef __APPLE__
#include <Python/Python.h>
#else
#include <Python.h>
#endif

#ifndef PythonScripts_H
#define PythonScripts_H
class PythonScripts {
    private:
        PyObject *uartModule;
        PyObject *httpModule;
    public:
        int init();
        PyObject* loadModule(const char *name);

        int readUART();

        void send(const char* path, PyObject *parameters);
};
#endif
