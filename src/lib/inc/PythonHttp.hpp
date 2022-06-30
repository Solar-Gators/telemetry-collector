#ifdef __APPLE__
#include <Python/Python.h>
#else
#include <Python.h>
#endif
class PythonHttp {
    private:
        PyObject *parameters;
        void addParameter(char* name, PyObject* value);
    public:
        void init();
        void addData(char* name, uint32_t data);
        void addData(char* name, uint16_t data);
        void addData(char* name, bool data);
        PyObject* getParameters();
        void flush();
};
