// UTIL.c
#include "Utils.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <BluetoothSerial.h>
#include <Arduino.h>

BluetoothSerial ESP_BT;

// this file is completely wrong and will probably be wiped and completely re-
// written

void util_setup_peripheral(PeripheralType type) {
  switch (type) {
        case PERIPHERAL_CELL:
            // Initialization specific to the cellular module
            // This could involve setting up serial ports, configuring AT commands,
            // and ensuring the module is ready for communication

            break;
        case PERIPHERAL_BT:
            // Initialization specific to the cellular module
            // This could involve setting up serial ports, configuring AT commands,
            // and ensuring the module is ready for communication
            break;
    }
}

bool util_check_connection() {
    // Code to check the BLE connection status
    return false; // Placeholder return value
}

void util_reconnect() {
    // Code to attempt reconnection
}

char* util_serialize_data(void* data, size_t dataSize) {
    // Code to serialize data
    return ""; // Placeholder return value
}

void util_confirm_response() {
    // Code to confirm that the mobile app received the data
}



