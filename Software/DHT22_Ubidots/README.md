## Output
![](https://github.com/DochevM/Seeed-Studio-XIAO-ESP32S3/blob/main/Documents/Output_Ubidots.png)

## Connections

| Raspberry Pi Pico  |       DHT22        |
| ------------------ | -------------------|
| 3,3V               | Vcc                |
| GP14               | Data               |
| GND                | GND                |


![alt text](https://github.com/DochevM/Seeed-Studio-XIAO-ESP32S3/blob/main/Documents/_XIAO_ESP32_Pinout.png)

## Software Preparation

- Add ESP32 board package to your Arduino IDE.
 Navigate to File > Preferences, and fill "Additional Boards Manager URLs" with the url below: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

 Navigate to Tools > Board > Boards Manager..., type the keyword esp32 in the search box, select the latest version of esp32, and install it.

 # <span style="color:red;">Important!!</span>
- The on-board package for XIAO ESP32S3 requires at least version 2.0.8 to be available, but for this example it shoud be up to 2.0.17, because from 3.0.0 its not working properly in this case.

  
- Also in the code Edit: 
```
const char* ubidotsToken = "PUT YOUR TOKEN HERE"; // Replace with your Ubidots Token
const char* deviceLabel = "YOUR DEVICE LABEL"; // Device label
```
and 
```
    String serverPath = "http://things.ubidots.com/api/v1.6/devices/" + String(deviceLabel);
//if you are a industrial user use: http://industrial.api.ubidots.com/api/v1.6/devices/
```
