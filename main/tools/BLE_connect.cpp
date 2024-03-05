#include "BLE_connect.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
long lastMsgTime = 0; // To keep track of the last message time

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


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

// This function recieves messages from Mobile APP
// Define the characteristic callback class 
// THIS CAN CALL UPDATE PREFERENCES ON ITS OWN!!!!!
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string rxValue = pCharacteristic->getValue();

        if (rxValue.length() > 0) {
            Serial.println("Received Value: ");
            for (int i = 0; i < rxValue.length(); i++)
                Serial.print(rxValue[i]);

            Serial.println();
        }
    }
};

BLEConnect::BLEConnect() {
    // Constructor code here (if necessary)
}

void BLEConnect::initializeBLE() {
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

bool BLEConnect::isBTEConnected() {
    return deviceConnected; // updated by connection callback
}

void BLEConnect::handleConnection() {
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


void BLEConnect::sendTrigger() {
    if(deviceConnected){
        std::string msg = checkPreferencesBT(); // this needs to reply with something prob
        pCharacteristic->setValue(msg.c_str());
        pCharacteristic->notify();
    } else switchToCell(); // if device disconnected after check send over cell?
    // Sends trigger information to the mobile app when an RFID event is detected
}
