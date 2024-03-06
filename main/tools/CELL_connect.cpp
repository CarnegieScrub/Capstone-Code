#include "CELL_connect.h"
#include <stdlib.h>
#include <string>
#include <Preferences.h>

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
    std::string AppMsg = checkPreferencesCELL(TriggerInfo); // this needs to reply with something prob
}
