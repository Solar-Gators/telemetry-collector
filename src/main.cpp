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
        rx_module->FromByteArray();
        rx_module->PostTelemetry();

        // if (network.can_id == mit.can_id_) {
            // mit.FromByteArray(network.data);
            // PyObject *parameters = PyDict_New();
            // PyDict_SetItemString(parameters, "battVoltage",
            //     PyLong_FromLong(mit.GetBatteryVoltage())
            // );

            // PyDict_SetItemString(parameters, "battCurrent",
            //     PyLong_FromLong(mit.GetBatteryCurrent())
            // );

            // PyDict_SetItemString(parameters, "motorCurrentPkAvg",
            //     PyLong_FromLong(mit.GetMotorCurrentPkAvg())
            // );

            // PyDict_SetItemString(parameters, "FETtemp",
            //     PyLong_FromLong(mit.GetFetTemp())
            // );

            // PyDict_SetItemString(parameters, "motorRPM",
            //     PyLong_FromLong(mit.GetMotorRPM())
            // );

            // PyDict_SetItemString(parameters, "PWMDuty",
            //     PyLong_FromLong(mit.GetPWMDuty())
            // );

            // PyDict_SetItemString(parameters, "LeadAngle",
            //     PyLong_FromLong(mit.GetLeadAngle())
            // );
            // scripts.sendData(parameters);

            // dataLink.flush();
        // }

        dataLink.flush();
    }

    return 0;
}
