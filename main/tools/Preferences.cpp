#include "Preferences.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "vector"

// string array for names of all preferences (ie both cell and BT have it)
static const std::vector<std::string> ALLPreferences = {
    "SOS1",
    "SOS2",
    "SOS3",
    "911",
};

// preferences just for BT
static const std::vector<std::string> BTPreferences = {
    "BTpref1",
    "pref2",
    "pref3",
};

// preferences just for cell
static const std::vector<std::string> CELLPreferences = {
    "CELLpref1",
    "pref2",
    "pref3",
};

// on main init this will load all the stored preferences. 
void Preferences::InitPreferences() {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

// loads preference key value from storage into retVal 
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

void Preferences::savePreferences(const std::string& preference, const std::string& prefval) {
    // Save/Update preferences to storage
    nvs_handle_t my_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &my_handle));
    ESP_ERROR_CHECK(nvs_set_str(my_handle, preference, prefval.c_str()));
    ESP_ERROR_CHECK(nvs_commit(my_handle));
    nvs_close(my_handle);
}

std::vector<std::string> parseTriggerInfo(const std::string& Trigger){ // prob should go in util?
    // will return a tuple, ["call" or "text", phone_number, message_data?]


    
}

void Preferences::checkPreferencesCELL(const std::string& Trigger) {

    std::vector<std::string> RetArr = parseTriggerInfo(const std::string& Trigger);
    if(RetArr[0] == "call"){
        // call 
        int number = RetArr[1];
        std::string msg = RetArr[2];
        // make call with message????????

    } else {
        // text
    }
    // Check and return proper trigger info for Cellular based on preferences
}
