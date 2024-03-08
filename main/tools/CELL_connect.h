#ifndef CELL_CONNECT_H
#define CELL_CONNECT_H

class CellularManager {
public:
    static CellularManager& getInstance(); // Declaration of the static method to access the instance

    CellularManager();
    void initializeCellular();
    void sendSMS();
    void makeCall();
    void sendCELLTrigger(std::string TriggerInfo);

    CellularManager(const CellularManager&) = delete;
    CellularManager& operator=(const CellularManager&) = delete;
};

#endif // CELL_CONNECT_H
