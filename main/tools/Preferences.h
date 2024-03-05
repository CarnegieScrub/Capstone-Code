#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <stdlib.h>
#include <string>

class Preferences {
public:
    Preferences();
    void loadPreferences();
    void savePreferences();
    void updatePreferences();
    std::string checkPreferencesBT(const std::string& Trigger, int num_trigs);
    void checkPreferencesCELL();
};

#endif
