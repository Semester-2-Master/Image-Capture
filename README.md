# Pollen Project firmware
## Hardware setup
Running this project requires the following hardware:
* [ESP32-CAM](https://docs.ai-thinker.com/en/esp32-cam) development board by Ai-Thinker with an OV2640 camera module
* MG995 compatible continuous servo motor

Connect the ESP32's GPIO 13 to the servo's signal input and make sure both the ESP32 boards and the servo have stable 5V power supplies.
## Prerequisites
The firmware is compiled and uploaded to the ESP32 via [Arduino IDE](https://www.arduino.cc/en/software).

To use Arduino IDE with ESP32 microcontrollers, install version 2.0.11 of Espressif's [Arduino core for ESP32](https://github.com/espressif/arduino-esp32) by following the instructions in the [official documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide).

Use the library manager to install version 1.2.1 of [ESP32Servo](https://github.com/madhephaestus/ESP32Servo) library.
## Pollen trap setup
Setting up the pollen trap for operation consists of two stages. First the microscope has to be manually calibrated, then it can run the PollenCapture firmware.
### Calibration
1. Open the CalibrationServer sketch in Arduino IDE.
2. Set WiFi credentials in `CalibrationServer.ino` (line 26 & 27).
3. Upload the program to the ESP32-CAM.
4. Open the IP address printed on the serial console in a web browser and click the "Start stream" button. A live feed of the microscope camera should appear.
5. Put some pollen on the tape above the microscope lens and turn the calibration screw until pollen particles in the picture are in focus.

### Operation
1. Open the PollenCapture sketch in Arduino IDE.
2. Set WiFi credentials in `wifi_client.cpp` (line 4 & 5).
3. Set API URL in `http_client.cpp` (line 5).
4. Upload the program to the ESP32-CAM.
5. Place the device at the sampling location and turn it on.
6. It should upload three testing pictures to the server with 30 seconds delay, then start sending one picture every 30 minutes.
