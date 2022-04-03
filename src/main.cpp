#include "lib/inc/DataLinkRecive.hpp"
#include "lib/inc/PythonScripts.hpp"


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
