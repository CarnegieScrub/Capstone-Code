#ifndef CELL_CONNECT_H
#define CELL_CONNECT_H

class CELLConnect {
public:
    CELLConnect();
    void initializeCellular();
    void sendSMS();
    void makeCall();
    void sendCELLTrigger(std::string TriggerInfo);
};

#endif // CELL_CONNECT_H
