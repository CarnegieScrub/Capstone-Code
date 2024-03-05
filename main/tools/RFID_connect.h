#ifndef RFID_CONNECT_H
#define RFID_CONNECT_H

class RFIDConnect {
public:
    RFIDConnect();
    void initializeRFID();
    void checkForTag();
    void triggeredCommunication();
};

#endif
