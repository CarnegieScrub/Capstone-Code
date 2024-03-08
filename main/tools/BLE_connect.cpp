#include "CPU.h"    // Pendant main CPU code
#include "Preferences.h"   // SOS contacts and Trigger Preferences code
#include "Utils.h"   // Utility/helper function code
#include "BLE_connect.h"    // Pendant -> Mobile App communication
#include "CELL_connect.h"   // Pendant -> Cellular communication
#include "RFID_connect.h"   // Ring -> Pendent RFID communication
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
long lastMsgTime = 0; // To keep track of the last message time

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

Preferences* prefs = Preferences::getInstance();

// Implement the static method to get the instance
BluetoothManager& BluetoothManager::getInstance() {
    static BluetoothManager instance; // Guaranteed to be created only once
    return instance;
}

// This sets connection status
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Device connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Device disconnected");
    }
};

/* This function recieves messages from Mobile APP
* Define the characteristic callback class 
* set the rxValue.find to different values and (19) is
* start of substring 
*/ 
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxValue = pCharacteristic->getValue();
        if (rxValue.length() > 0) {
            Serial.println("Received Value: " + String(rxValue.c_str()));
            if (rxValue.find("preferences update SOS1") == 0) {
                std::string value = rxValue.substr(19);
                prefs->savePreferences("SOS1", value);
                Serial.println("SOS1 Preference saved: " + String(value.c_str()));
            } else if (rxValue.find("preferences update SOS2") == 0) {
                std::string value = rxValue.substr(19);
                prefs->savePreferences("SOS2", value);
                Serial.println("SOS2 Preference saved: " + String(value.c_str()));
            } else if (rxValue.find("preferences update SOS3") == 0) {
                std::string value = rxValue.substr(19);
                prefs->savePreferences("SOS3", value);
                Serial.println("SOS3 Preference saved: " + String(value.c_str()));
            }
        }
    }
};

// BLEConnect::BLEConnect() {
//     // Constructor code here (if necessary prob not)
// }

void BluetoothManager::initializeBLE() {
    // Sets up BLE advertisement and service characteristics
    Serial.begin(115200);
    BLEDevice::init("ESP32");

    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ |
                        BLECharacteristic::PROPERTY_WRITE |
                        BLECharacteristic::PROPERTY_NOTIFY
                        );

    // Attach the custom callbacks to the characteristic
    pCharacteristic->setCallbacks(new MyCallbacks());
    
    pCharacteristic->addDescriptor(new BLE2902());

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x0);
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}

bool BluetoothManager::isBTEConnected() {
    return deviceConnected; // updated by connection callback
}

void BluetoothManager::handleConnection() {
    // Check for connection/disconnection
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the BLE stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("Start advertising");
        oldDeviceConnected = deviceConnected;
    }
    
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
    }
}


void BluetoothManager::sendBLETrigger(std::string TriggerInfo) {
    if(deviceConnected){
        // get serialize message for trigger and send back to app
        pCharacteristic->setValue(TriggerInfo.c_str());
        pCharacteristic->notify();
    } else sendCELLTrigger(TriggerInfo); // if device disconnected after check send over cell?
    // Sends trigger information to the mobile app when an RFID event is detected
}
