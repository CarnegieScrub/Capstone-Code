#ifndef BLE_CONNECT_H
#define BLE_CONNECT_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string>


// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>
// BluetoothManager.h

#include <string> // Include necessary libraries

class BluetoothManager {
public:
    static BluetoothManager& getInstance(); // Declaration of the static method to access the instance

    void initializeBLE();
    bool isBTEConnected();
    void handleConnection();
    void sendBLETrigger(std::string TriggerInfo);
    // Delete copy constructor and copy assignment operator to prevent duplicates
    BluetoothManager(const BluetoothManager&) = delete;
    BluetoothManager& operator=(const BluetoothManager&) = delete;
};

#endif // BLUETOOTH_MANAGER_H

// class BLEConnect {
// public:
//     BLEConnect();
//     void initializeBLE();
//     bool isBTEConnected();
//     void handleConnection();
//     void sendBLETrigger(std::string TriggerInfo);
// };         

// #endif // BLE_CONNECT_H
