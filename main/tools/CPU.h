#ifndef CPU_H
#define CPU_H

class CPU {
public:
    CPU();
    void initializeCPU();
    void checkBatteryLevel();
    void enterLowPowerMode();
    void exitLowPowerMode();
    void monitorSystemHealth();
};

#endif
