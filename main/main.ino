#include "tools/CPU.h"    // Pendant main CPU code
#include "tools/Preferences.h"   // SOS contacts and Trigger Preferences code
#include "tools/Utils.h"   // Utility/helper function code
#include "tools/BLE_connect.h"    // Pendant -> Mobile App communication
#include "tools/CELL_connect.h"   // Pendant -> Cellular communication
#include "tools/RFID_connect.h"   // Ring -> Pendent RFID communication

// before compiling remove from tools/ directory. 

void initSystem() {
  initializeCPU();   // CPU.h initialize esp32 as CPU controller (battery, GPIO, UART etc comms between devices) 
  initializeBLE();   // BLE_connect.h Initialize Bluetooth connection
  loadPreferences();  // Prefences.h Initialize Prefences and sets/store proper data from app
  initializeCellular();  // CELL_connect.h Initialize Cellular setup
  initializeRFID();  // RFID_connect.h Initialize RFID setup 
}


void setup(){
  Serial.begin(115200);
  initSystem(); // init systems
}


void loop() {
  // if RFID trigger detected
  if (checkForTag()) { // RFID.h receives prelim trigger
    if (triggered_communication()) { // RFID.h parses triggers and ensures cancellation or more triggers are allowed
      unsigned long startTime = millis();
      while (millis() - startTime < 10000) { // wait 10 seconds
        if (isBTEConnected()) { // BLE_connect.h checker function 
          send_BTE_trigger();   // BLE_connect.h sender function 
          break;
        }
      }
      if (!isBTEConnected()) { // BLE_connect.h checker function 
        send_CELL_trigger(); // CELL_connect.h, sends cell trigger
      }
    }
  }
}
