#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <vector>
#include <string>

class Preferences {
private:
    static Preferences* instance; // Static instance pointer
    // Other private members...

    Preferences() {} // Private constructor to prevent external instantiation

public:
    // Deleted copy constructor and assignment operator to enforce singleton property
    Preferences(const Preferences&) = delete;
    Preferences& operator=(const Preferences&) = delete;

    // Static method to access the singleton instance
    static Preferences* getInstance() {
        if (instance == nullptr) {
            instance = new Preferences();
        }
        return instance;
    }
    
    void InitPreferences();
    void loadPreferences(const std::string& preference, const std::string& prefval);
    void savePreferences(const std::string& preference, const std::string& prefval);
    std::vector<std::string> parseTriggerInfo(const std::string& Trigger);
    std::string checkPreferencesBT(const std::string& Trigger, int num_trigs);
    void checkPreferencesCELL(const std::string& Trigger);
};

#endif
