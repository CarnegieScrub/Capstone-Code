#include "CPU.h"    // Pendant main CPU code
#include "Preferences.h"   // SOS contacts and Trigger Preferences code
#include "Utils.h"   // Utility/helper function code
#include "BLE_connect.h"    // Pendant -> Mobile App communication
#include "CELL_connect.h"   // Pendant -> Cellular communication
#include "RFID_connect.h"   // Ring -> Pendent RFID communication
#include <serial.h> 
#include <Arduino.h>

// before compiling remove from tools/ directory. 
CPU myCPU;
Preferences myPref;
BLEConnect BLE;
CELLConnect Cell;
RFIDConnect RFID;
Preferences* prefs = Preferences::getInstance();

void initSystem() {

  myCPU.initializeCPU();   // CPU.h initialize esp32 as CPU controller (battery, GPIO, UART etc comms between devices) 
  BLE.initializeBLE();   // BLE_connect.h Initialize Bluetooth connection
  prefs->InitPreferences();  // Prefences.h Initialize Prefences and sets/store proper data from app
  Cell.initializeCellular();  // CELL_connect.h Initialize Cellular setup
  RFID.initializeRFID();  // RFID_connect.h Initialize RFID setup 
}


void setup(){
  Serial.begin(115200);
  initSystem(); // init systems
}


void loop() {
  // if RFID trigger detected
  if (RFID.checkForTag()) { // RFID.h receives prelim trigger
    std::string TriggerInfo = RFID.triggeredCommunication(); // RFID.h parses triggers and ensures cancellation or more triggers are allowed
    if (TriggerInfo != "falseAlarm") { 
      unsigned long startTime = millis();
      while (millis() - startTime < 10000) { // wait 10 seconds
        if (BLE.isBTEConnected()) { // BLE_connect.h checker function 
          BLE.sendBLETrigger(TriggerInfo);   // BLE_connect.h sender function 
          break;
        }
      }
      if (!BLE.isBTEConnected()) { // BLE_connect.h checker function 
        Cell.sendCELLTrigger(TriggerInfo); // CELL_connect.h, sends cell trigger
      }
    }
  }
}
