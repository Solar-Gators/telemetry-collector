#include <map>
#include <iostream>
#include <sstream>
#include "lib/inc/DataLinkRecive.hpp"
#include "lib/inc/PythonScripts.hpp"
#include "lib/inc/NetworkReceive.hpp"
#include <Mitsuba.hpp>

int main(int argc, char *argv[]) {
    PythonScripts scripts;
    scripts.init();

    DataLinkReceive dataLink;
    dataLink.init();

    std::map<int, SolarGators::DataModules::DataModule*> modules;
    SolarGators::DataModules::MitsubaRx0 mit(0x08850225, 0);

    // //Datamodule registration
    modules.insert(std::make_pair(mit.can_id_, &mit));

    SolarGators::DataModules::DataModule* rx_module = (*modules.find(0x08850225)).second;

    int timeout = 0;

    while (1) {
        u_int8_t data = scripts.readUART();
        if (dataLink.read(data)) {
            NetworkReceive network;
            network.fromByteArray(dataLink.buffer);
            printf("CAN ID: %08x\n", network.can_id);
            printf("INSTANCE ID: %02x\n", network.instance_id);
            printf("SIZE: %02x\n", network.size);
            printf("DATA: ");
            for (int i = 0; i < network.size; i++) {
                printf("%02x ", network.data[i]);
            }
            printf("\n");

            // SolarGators::DataModules::DataModule* rx_module = (*modules.find(network.can_id)).second;
            // if(rx_module != nullptr) {
            //     rx_module->FromByteArray(data);
            //     //if (rx_module)
            // }

            if (network.can_id == mit.can_id_) {
                mit.FromByteArray(network.data);
                PyObject *parameters = PyDict_New();
                PyDict_SetItemString(parameters, "battVoltage",
                    PyLong_FromLong(mit.GetBatteryVoltage())
                );

                PyDict_SetItemString(parameters, "battCurrent",
                    PyLong_FromLong(mit.GetBatteryCurrent())
                );

                PyDict_SetItemString(parameters, "motorCurrentPkAvg",
                    PyLong_FromLong(mit.GetMotorCurrentPkAvg())
                );

                PyDict_SetItemString(parameters, "FETtemp",
                    PyLong_FromLong(mit.GetFetTemp())
                );

                PyDict_SetItemString(parameters, "motorRPM",
                    PyLong_FromLong(mit.GetMotorRPM())
                );

                PyDict_SetItemString(parameters, "PWMDuty",
                    PyLong_FromLong(mit.GetPWMDuty())
                );

                PyDict_SetItemString(parameters, "LeadAngle",
                    PyLong_FromLong(mit.GetLeadAngle())
                );
                scripts.sendData(parameters);
            }

            dataLink.flush();
        }
        timeout++;
    }

    return 0;
}
