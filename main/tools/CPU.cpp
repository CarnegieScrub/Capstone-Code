#include "CPU.h"
#include "Arduino.h"

CPU::CPU() {}

void CPU::initializeCPU() {
    // Set up CPU-specific configurations
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
}

void CPU::checkBatteryLevel() {
    // Return current battery level as a percentage
    // Read the battery voltage through an ADC pin.
    // Assuming a battery voltage divider is connected to GPIO 34 (Analog ADC1_CHANNEL_6)
    const int batteryPin = 34;
    const float maxBatteryVoltage = 4.2; // Max LiPo battery voltage
    const float minBatteryVoltage = 3.3; // Min LiPo battery voltage before shutdown

    // Configure ADC
    analogReadResolution(12); // Set the resolution to 12-bit (0 - 4095)
    analogSetAttenuation(ADC_11db); // For full range voltage measurement

    // Read battery level
    int readValue = analogRead(batteryPin);
    float voltage = (readValue / 4095.0) * 3.3; // Convert to voltage
    voltage *= 2; // If using a voltage divider that halves the voltage
    
    // Calculate battery percentage
    float batteryPercentage = (voltage - minBatteryVoltage) / (maxBatteryVoltage - minBatteryVoltage);
    batteryPercentage = constrain(batteryPercentage, 0.0, 1.0) * 100; // Constrain between 0-100%

    Serial.print("Battery level: ");
    Serial.print(batteryPercentage);
    Serial.println("%");
}

void CPU::enterLowPowerMode() {
    // Enter low-power state to conserve battery
    // This will stop the CPU and most of the peripherals
    esp_sleep_enable_timer_wakeup(1000000); // Wake up after 1 second (1e6 microseconds)
    esp_deep_sleep_start();
}

// might need an is charging function

void CPU::exitLowPowerMode() {
    // Exit low-power state in response to an event ( charging???)
}

void CPU::monitorSystemHealth() {
    // Check system health and functionality
}
