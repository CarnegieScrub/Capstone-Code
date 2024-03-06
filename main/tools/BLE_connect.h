#ifndef BLE_CONNECT_H
#define BLE_CONNECT_H

// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>

class BLEConnect {
public:
    BLEConnect();
    void initializeBLE();
    bool isBTEConnected();
    void handleConnection();
    void sendBLETrigger(std::string TriggerInfo);
};         

#endif // BLE_CONNECT_H
