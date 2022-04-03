#include <Python/Python.h>
#include <stdlib.h>
#define START 0xFF
#define END 0x3F
#define ESCAPE 0x2F
#define MAX_BUFFER_SIZE 5000

class DataLinkReceive {
    private:
        bool escaped;
        bool in_progress;

    public:
        u_int8_t buffer[MAX_BUFFER_SIZE];
        int arrayIndex;
        void flush() {
            this->arrayIndex = 0;
            this->escaped = false;
            this->in_progress = false;
        }

        bool read(u_int8_t data) {
            if (this->escaped) {
                this->escaped = false;
                return false;
            }

            if (data == ESCAPE) {
                this->escaped = true;
                return false;
            }

            if (data == START) {
                if (this->in_progress) {
                    this->flush();
                    printf("Error: There was multiple start conditions\n, data: %d", data);
                    return false;
                }
                this->in_progress = true;
                return false;
            }

            if (data == END) {
                if (!this->in_progress) {
                    this->flush();
                    printf("Error: There was an end condition without a start\n");
                    return false;
                }
                this->in_progress = false;
                return true;
            }

            if (!this->in_progress) {
                this->flush();
                printf("Error: There must be a start condition before a transmission can occour\n");
                return false;
            }

            this->buffer[this->arrayIndex] = data;
            this->arrayIndex++;
            return false;
        }
};

class PythonScripts {
    private:
        PyObject *uartModule;
        PyObject *httpModule;
    public:
        int init() {
            Py_Initialize();
            PyRun_SimpleString("import sys");
            PyRun_SimpleString("sys.path.append(\".\")");
            this->uartModule = this->loadModule("uart");
            this->httpModule = this->loadModule("dict");
            return 0;
        }
        PyObject* loadModule(const char *name) {
            PyObject *module = PyImport_ImportModule(name);
            if (module == NULL) {
                printf("Error loading a module\n");
                PyErr_Print();
            }
            return module;
        }
    
        int readUART() {
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

        void sendData() {
            PyObject *parameters = PyDict_New();
            PyObject *world = PyString_FromString("World");
            PyDict_SetItemString(parameters, "Hellos", world);
            PyObject *method = PyString_FromString("run");
            PyObject *response = PyObject_CallMethodObjArgs(this->httpModule, method, parameters, NULL);
            Py_DECREF(parameters);
            Py_DECREF(method);
            Py_DECREF(world);
            Py_DECREF(response);
        }
};


int main(int argc, char *argv[]) {
    PythonScripts scripts;
    scripts.init();

    DataLinkReceive dataLink;
    int timeout = 0;

    while (timeout < 30) {
        u_int8_t data = scripts.readUART();
        if (dataLink.read(data)) {

            uint8_t* buff = dataLink.buffer;
            printf("CAN ID: %08x\n", (int)buff[3] | ((int)buff[2] << 8) | ((int)buff[1] << 16) | ((int)buff[0] << 24));
            printf("INSTANCE ID: %02x\n", buff[4]);
            int size = buff[5];
            printf("SIZE: %02x\n", size);
            printf("DATA: ");
            for (int i = 0; i < size; i++) {
                printf("%02x ", dataLink.buffer[i + 6]);
            }
            printf("\n");

            dataLink.flush();
        }
        timeout++;
    }

    return 0;
}
