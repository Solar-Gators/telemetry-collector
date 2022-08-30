#include <map>
#include <iostream>
#include <sstream>
#include "DataLinkRecive.hpp"
#include "PythonScripts.hpp"
#include "NetworkReceive.hpp"
#include "DataModule.hpp"
#include "Mitsuba.hpp"
#include "Mitsuba.hpp"
#include "OrionBMS.hpp"
#include "DataModuleInfo.hpp"

SolarGators::DataModules::MitsubaRx0 MitsubaRx0(SolarGators::DataModuleInfo::MOTORRX0_RL_MSG_ID, 0);
SolarGators::DataModules::MitsubaRx1 MitsubaRx1(SolarGators::DataModuleInfo::MOTORRX1_RL_MSG_ID, 0);
SolarGators::DataModules::MitsubaRx2 MitsubaRx2(SolarGators::DataModuleInfo::MOTORRX2_RL_MSG_ID, 0);

SolarGators::DataModules::OrionBMSRx0 OrionBMSRx0(SolarGators::DataModuleInfo::BMS_RX0_MSG_ID, 0);
SolarGators::DataModules::OrionBMSRx1 OrionBMSRx1(SolarGators::DataModuleInfo::BMS_RX1_MSG_ID, 0);
SolarGators::DataModules::OrionBMSRx2 OrionBMSRx2(SolarGators::DataModuleInfo::BMS_RX2_MSG_ID, 0);
SolarGators::DataModules::OrionBMSRx3 OrionBMSRx3(SolarGators::DataModuleInfo::BMS_RX3_MSG_ID, 0);
SolarGators::DataModules::OrionBMSRx4 OrionBMSRx4(SolarGators::DataModuleInfo::BMS_RX4_MSG_ID, 0);
SolarGators::DataModules::OrionBMSRx5 OrionBMSRx5(SolarGators::DataModuleInfo::BMS_RX5_MSG_ID, 0);

int main(int argc, char *argv[]) {
    PythonScripts scripts;
    scripts.init();

    DataLinkReceive dataLink;
    dataLink.init();

    std::map<int, SolarGators::DataModules::DataModule*> modules;


    // //Data module registration
    modules.insert(std::make_pair(MitsubaRx0.can_id_, &MitsubaRx0));
    modules.insert(std::make_pair(MitsubaRx1.can_id_, &MitsubaRx1));
    modules.insert(std::make_pair(MitsubaRx2.can_id_, &MitsubaRx2));
    modules.insert(std::make_pair(OrionBMSRx0.can_id_, &OrionBMSRx0));
    modules.insert(std::make_pair(OrionBMSRx1.can_id_, &OrionBMSRx1));
    modules.insert(std::make_pair(OrionBMSRx2.can_id_, &OrionBMSRx2));
    modules.insert(std::make_pair(OrionBMSRx3.can_id_, &OrionBMSRx3));
    modules.insert(std::make_pair(OrionBMSRx4.can_id_, &OrionBMSRx4));
    modules.insert(std::make_pair(OrionBMSRx5.can_id_, &OrionBMSRx5));

    NetworkReceive network;
    while (1) {
        u_int8_t data = scripts.readUART();
        if (!dataLink.read(data)) {
            continue;
        }
        network.fromByteArray(dataLink.buffer);
        //Get module
        SolarGators::DataModules::DataModule* rx_module = (*modules.find(network.can_id)).second;
        if (modules.count(network.can_id) > 0) {
            rx_module->FromByteArray(network.data);
            rx_module->PostTelemetry(&scripts);
        }
        dataLink.flush();
    }

    return 0;
}
