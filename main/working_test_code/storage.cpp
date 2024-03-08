#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <nvs_flash.h>
#include <nvs.h>
#include <string>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
long lastMsgTime = 0; // To keep track of the last message time

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

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

void savePreference(const std::string& key, const std::string& value) {
    nvs_handle_t my_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &my_handle));
    ESP_ERROR_CHECK(nvs_set_str(my_handle, key.c_str(), value.c_str()));
    ESP_ERROR_CHECK(nvs_commit(my_handle));
    nvs_close(my_handle);
}

bool loadPreference(const std::string& key, std::string& value) {
    nvs_handle_t my_handle;
    esp_err_t err;
    size_t required_size;
    err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err != ESP_OK) return false;

    err = nvs_get_str(my_handle, key.c_str(), nullptr, &required_size);
    if (err != ESP_OK) {
        nvs_close(my_handle);
        return false;
    }

    char* buf = new char[required_size];
    err = nvs_get_str(my_handle, key.c_str(), buf, &required_size);
    if (err == ESP_OK) {
        value.assign(buf, required_size - 1);
    }
    delete[] buf;
    nvs_close(my_handle);
    return err == ESP_OK;
}

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string rxValue = pCharacteristic->getValue();
        if (rxValue.length() > 0) {
            Serial.println("Received Value: " + String(rxValue.c_str()));
            if (rxValue.find("preferences update") == 0) {
                std::string value = rxValue.substr(19);
                savePreference("Pref1", value);
                Serial.println("Preference saved: " + String(value.c_str()));
            }
        }
    }
};

void setup() {
  Serial.begin(115200);

  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

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

void loop() {
    if (deviceConnected) {
        std::string value;
        if (loadPreference("Pref1", value)) {
            Serial.println("Stored preference: " + String(value.c_str()));
        } else {
            Serial.println("No preference stored.");
        }
        delay(10000); // Delay for demonstration purposes
    }
}
