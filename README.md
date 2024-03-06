# Guardian - Discreet Personal Safety Wearable

---
## 🟢: Confirmed Design Choice
---
## 🟡: Needs approval 
---
## 🔴: Undiscussed important issues 
🛰️ur mom



## Overview

Guardian is a discreet safety jewelry system designed to empower users by providing immediate assistance in threatening situations. It seamlessly integrates advanced safety features into everyday accessories such as rings and pendants. Users can activate these features discreetly, without drawing attention, ensuring a balance between physical and digital protection.

## System Components

- **Pendant**: Central to the system, featuring BLE and cellular communication, GPS tracking, voice detection, and an RFID interface for user interaction.
- **Mobile App**: A companion application for configuring the pendant, managing emergency contacts, and receiving notifications.
- **Ring**: An accessory that works in tandem with the pendant, utilizing RFID for communication.

## Directory Structure

```
/Guardian
  ├── /main
  │     ├── main.ino
  │     └── /tools
  │         ├── BLE_connect.cpp
  │         ├── BLE_connect.h
  │         ├── CELL_connect.cpp
  │         ├── CELL_connect.h
  │         ├── CPU.cpp
  │         ├── CPU.h
  │         ├── Preferences.cpp
  │         ├── Preferences.h
  │         ├── RFID_connect.cpp
  │         ├── RFID_connect.h
  │         ├── Utils.cpp
  │         └── Utils.h
  └── /MobileAppCode
        └── (various mobile app project files)
```

## Project Features

- **Emergency SOS**: Quick activation via the pendant or ring sends alerts to emergency services and pre-defined contacts.
- **Customizable Triggers**: Multiple triggers can be customized through the app, such as ring presses, voice activation, and geofencing.
- **Offline Compatibility**: The system can function without a mobile device, sending alerts through cellular networks.

## Setup and Configuration

1. **Pendant**: Flash the `main/main.ino` sketch onto the ESP32 microcontroller within the pendant.
2. **Mobile App**: Build and install the app from the `/MobileAppCode` directory onto a smartphone.
   2.1 Install nRF connect ESP communication development testing on iOS or Android.
4. **Pairing**: Use the mobile app to pair with the pendant via Bluetooth and set up emergency contacts and preferences.

## Usage

- **Activation**: Press the ring or use the voice trigger to activate the SOS feature.
- **Configuration**: Set up emergency contacts and customize trigger settings within the mobile app.
- **Alerts**: Receive notifications on the app and/or through cellular communication when the SOS feature is activated.

## Testing

- Refer to the design document for detailed test plans, including connectivity, data serialization, and processing, to ensure the system meets all design specifications and user requirements.

## License

- The project is licensed under [scrubs]. See the `LICENSE` file for more details.

## Contact

- For any additional queries or assistance, reach out to the team via tamal@andrew.cmu.edu and tell him u love group b5.

## Acknowledgments

- Thanks to the team members and advisors at Carnegie Mellon University's Electrical and Computer Engineering department for their support and guidance throughout the development of this project.

