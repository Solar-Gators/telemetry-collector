#include "inc/PythonHttp.hpp"

//public methods
void PythonHttp::init() {
    parameters = PyDict_New();
}

void PythonHttp::addData(char* name, uint32_t data) {
    addParameter(
      PyLong_FromLong(data)
    );
}

void PythonHttp::addData(char* name, uint16_t data) {
    addParameter(
        PyLong_FromLong(data)
    );
}

void PythonHttp::addData(char* name, bool data) {
    PyObject *value;
    if (data) {
        value = Py_True;
    }
    else {
        value = Py_False;
    }

    addParameter(value);
}

PyObject * PythonHttp::getParameters() {
    return parameters;
}

void PythonHttp::flush() {
    Py_DECREF(parameters);
}

//private methods
void PythonHttp::addParameter(char* name, PyObject* value) {
    PyDict_SetItemString(parameters, name, value);
}
