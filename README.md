Project Structure:

1. Main Module (Main.ino)
   - Description: Acts as the entry point of the application. Initializes the system components and manages the high-level flow control.
   - Functions:
     - setup(): Initializes Bluetooth, RFID, and cellular modules. Loads stored preferences and emergency contacts if available.
     - loop(): Main loop that checks for RFID triggers and manages communication between the pendant and the mobile app or cellular network as required.

2. Bluetooth Module (BLE_Connect.cpp / BLE_Connect.h)
   - Description: Manages Bluetooth Low Energy (BLE) communication with the mobile app.
   - Functions:
     - initializeBLE(): Sets up BLE advertisement and service characteristics.
     - handleConnection(): Manages BLE connections and disconnections.
     - receivePreferences(): Handles incoming messages from the mobile app, updating preferences and emergency contacts.
     - sendTrigger(): Sends trigger information to the mobile app when an RFID event is detected.

3. Cellular Module (CELL_Connect.cpp / CELL_Connect.h)
   - Description: Manages cellular communication for sending emergency alerts via SMS or voice call when BLE is not available.
   - Functions:
     - initializeCellular(): Establishes a cellular connection.
     - sendSMS(): Sends an SMS message to pre-configured emergency contacts.
     - makeCall(): Initiates a voice call to a pre-configured emergency contact.

4. RFID Module (RFID_Connect.cpp / RFID_Connect.h)
   - Description: Handles RFID reader interactions to detect button presses or tags.
   - Functions:
     - initializeRFID(): Configures RFID hardware for operation.
     - checkForTag(): Polls the RFID reader for new tags or button press events and triggers actions accordingly.

5. Preferences Manager (Preferences.cpp / Preferences.h)
   - Description: Manages user preferences and emergency contact information storage and retrieval.
   - Functions:
     - loadPreferences(): Loads preferences and contacts from non-volatile storage.
     - savePreferences(): Saves updated preferences and contacts to non-volatile storage.
     - updatePreferences(): Updates the current preferences in memory and storage based on received data.

6. Utilities (Utils.cpp / Utils.h)
   - Description: Provides utility functions that are used across multiple modules.
   - Functions:
     - formatMessage(): Formats messages for sending over cellular or BLE.
     - logError(): Utility function for logging errors to a central place, which could be serial output or external storage.

Directory Structure:
- /src: Contains the source files (.cpp) and header files (.h) for the project.
  - /src/main.ino: Main Arduino sketch.
  - /src/BLE_Connect.cpp: BLE functionality implementation.
  - /src/BLE_Connect.h: Header for BLE functionality.
  - /src/CELL_Connect.cpp: Cellular functionality implementation.
  - /src/CELL_Connect.h: Header for cellular functionality.
  - /src/RFID_Connect.cpp: RFID functionality implementation.
  - /src/RFID_Connect.h: Header for RFID functionality.
  - /src/Preferences.cpp: Preferences management implementation.
  - /src/Preferences.h: Header for preferences management.
  - /src/Utils.cpp: Utility functions implementation.
  - /src/Utils.h: Header for utility functions.

Development Notes:
- Non-Volatile Storage: Consider using ESP32's NVS (Non-Volatile Storage) library for storing preferences and emergency contacts. This ensures data persistence across reboots.
- Testing and Debugging: Implement logging at strategic points across modules to aid in debugging and monitoring the system's behavior during development and testing.
- Security: Ensure that data sent over BLE is encrypted, and implement authentication mechanisms to prevent unauthorized access.
