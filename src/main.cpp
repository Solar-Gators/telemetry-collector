#include <map>
#include "lib/inc/DataLinkRecive.hpp"
#include "lib/inc/PythonScripts.hpp"
#include "lib/inc/NetworkReceive.hpp"


int main(int argc, char *argv[]) {
    PythonScripts scripts;
    scripts.init();

    DataLinkReceive dataLink;
    dataLink.init();

    // std::map<int, > modules;

    // //Datamodule registration
    // modules.insert(std::make_pair(module->can_id_, module));
    // modules.insert(std::make_pair(module->can_id_, module));

    int timeout = 0;

    while (timeout < 30) {
        u_int8_t data = scripts.readUART();
        if (dataLink.read(data)) {
            NetworkReceive network;
            network.fromByteArray(dataLink.buffer);
            // printf("CAN ID: %08x\n", network.can_id);
            // printf("INSTANCE ID: %02x\n", network.instance_id);
            // printf("SIZE: %02x\n", network.size);
            // printf("DATA: ");
            // for (int i = 0; i < network.size; i++) {
            //     printf("%02x ", network.data[i]);
            // }
            // printf("\n");



            dataLink.flush();
        }
        timeout++;
    }

    return 0;
}
