#include <map>
#include <iostream>
#include <sstream>
#include "DataLinkRecive.hpp"
#include "PythonScripts.hpp"
#include "NetworkReceive.hpp"
#include "DataModule.hpp"
#include "Mitsuba.hpp"

int main(int argc, char *argv[]) {
    PythonScripts scripts;
    scripts.init();

    DataLinkReceive dataLink;
    dataLink.init();

    std::map<int, SolarGators::DataModules::DataModule*> modules;
    SolarGators::DataModules::MitsubaRx0 mit(0x08850225, 0);

    // //Data module registration
    modules.insert(std::make_pair(mit.can_id_, &mit));


    NetworkReceive network;
    while (1) {
        u_int8_t data = scripts.readUART();
        if (!dataLink.read(data)) {
            continue;
        }
        network.fromByteArray(dataLink.buffer);

        //Get module
        SolarGators::DataModules::DataModule* rx_module = (*modules.find(network.can_id)).second;
        rx_module->FromByteArray(network.data);
        rx_module->PostTelemetry(&scripts);
        dataLink.flush();
    }

    return 0;
}
