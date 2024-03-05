#include "Preferences.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "vector"

static const std::vector<std::string> ALLPreferences = {
    "allpref1",
    "pref2",
    "pref3",
};

static const std::vector<std::string> BTPreferences = {
    "BTpref1",
    "pref2",
    "pref3",
};

static const std::vector<std::string> CELLPreferences = {
    "CELLpref1",
    "pref2",
    "pref3",
};

Preferences::Preferences() {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void Preferences::loadPreferences(const std::string& preference, std::string& retVal) {
    // Load preferences from storage
    nvs_handle_t my_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READONLY, &my_handle));
    size_t required_size;
    ESP_ERROR_CHECK(nvs_get_str(my_handle, preference, NULL, &required_size));
    char* phone_buf = new char[required_size];
    ESP_ERROR_CHECK(nvs_get_str(my_handle, preference, phone_buf, &required_size));
    retVal = std::string(phone_buf);
    delete[] phone_buf;
    nvs_close(my_handle);
}

void Preferences::savePreferences(const std::string& preference, const std::string& prefval) {
    // Save/Update preferences to storage
    nvs_handle_t my_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &my_handle));
    ESP_ERROR_CHECK(nvs_set_str(my_handle, preference, prefval.c_str()));
    ESP_ERROR_CHECK(nvs_commit(my_handle));
    nvs_close(my_handle);
}

std::string Preferences::checkPreferencesBT(std::string TriggerInfo) {
    //
    // Check and return proper trigger info for Bluetooth based on preferences
    for (string in ALLPreferences):

    loadPreferences(..);
}

void Preferences::checkPreferencesCELL() {
    // Check and return proper trigger info for Cellular based on preferences
}
