#ifndef RFID_CONNECT_H
#define RFID_CONNECT_H

#include <string>

class RFIDConnect {
public:
    RFIDConnect();
    void initializeRFID();
    bool checkForTag();
    std::string triggeredCommunication();
};

#endif
