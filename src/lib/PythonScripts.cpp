#include "inc/PythonScripts.hpp"

int PythonScripts::init() {
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\"./src/python\")");
    this->uartModule = this->loadModule("uart");
    this->httpModule = this->loadModule("http");
    return 0;
}

PyObject* PythonScripts::loadModule(const char *name) {
    PyObject *module = PyImport_ImportModule(name);
    if (module == NULL) {
        printf("Error loading a module\n");
        PyErr_Print();
    }
    return module;
}

int PythonScripts::readUART() {
    PyObject *wait_for_transmission = PyObject_GetAttrString(this->uartModule, "wait_for_transmission");
    PyObject *byte = PyObject_CallFunction(wait_for_transmission, NULL);
    int value = 0;
    if (byte != NULL) {
        value = _PyInt_AsInt(byte);
        // printf("Result of call: %d\n", value);
    }
    else {
        printf("Error reading value\n");
        PyErr_Print();
    }
    Py_DECREF(byte);
    Py_DECREF(wait_for_transmission);
    return value;
}

void PythonScripts::sendData(char* path, PyObject *parameters) {
    PyObject *method = PyString_FromString("run");
    pyObject *pathPy = PyString_FromString(path);
    PyObject *response = PyObject_CallMethodObjArgs(
        this->httpModule,
        method,
        parameters,
        pathPy,
        NULL
    );
    Py_DECREF(method);
    Py_DECREF(pathPy);
    Py_DECREF(response);
}
