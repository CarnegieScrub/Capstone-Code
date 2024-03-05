#include "tools/BTE.h"
#include "tools/CELL.h"
#include "tools/RFID.h"
#include "tools/UTIL.h"

// before compiling remove from tools/ directory. 

void setup() {
  initBTE();   // Initialize Bluetooth
  initCELL();  // Initialize Cellular
  initRFID();  // Initialize RFID
  initUTIL();  // Initialize Utility functions if needed
}

void loop() {
  if (triggered_communication()) {
    unsigned long startTime = millis();
    while (millis() - startTime < 10000) {
      if (isBTEConnected()) { // Assume isBTEConnected() is a function that checks BLE connection
        send_BTE_trigger();
        break;
      }
    }
    if (!isBTEConnected()) {
      send_CELL_trigger();
    }
  }
}
