#include <stdlib.h>
#include <string>
#include <Preferences.h>
#include "CPU.h"    // Pendant main CPU code
#include "Preferences.h"   // SOS contacts and Trigger Preferences code
#include "Utils.h"   // Utility/helper function code
#include "BLE_connect.h"    // Pendant -> Mobile App communication
#include "CELL_connect.h"   // Pendant -> Cellular communication
#include "RFID_connect.h"   // Ring -> Pendent RFID communication

Preferences* prefs = Preferences::getInstance();

CELLConnect::CELLConnect() {
    // Constructor code here (if necessary)
}

void CELLConnect::initializeCellular() {
    // Establishes a cellular connection
}

void CELLConnect::sendSMS() {
    // Sends an SMS message to pre-configured emergency contacts
}

void CELLConnect::makeCall() {
    // Initiates a voice call to a pre-configured emergency contact
}

void sendCELLTrigger(std::string TriggerInfo){
    // sends proper cell trigger 
    std::string AppMsg = prefs->checkPreferencesCELL(TriggerInfo); // this needs to reply with something prob
}
