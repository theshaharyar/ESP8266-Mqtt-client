ESP8266 Simple MQTT client 
===========================================

This is a sample project that demonstrates how ESP8266 is used to process a message transmitted over a certain MQTT topic and then taking action based on certain parameter

# Contents
- [Libraries](#Libraries)
- [Contributing](#contributing)  
- [License and credits](#license-and-credits)   

### Libraries
- ESP8266WiFi.h
- PubSubClient.h
- Wire.h  (Only needed for Arduino 1.6.5 and earlier)
- ArduinoJson.h
- SSD1306.h 

### Contributing

For minor fixes of code and documentation, please go ahead and submit a pull request.

Larger changes (rewriting parts of existing code from scratch, adding new functions to the core, adding new libraries) should generally be discussed by opening an issue first.

Feature branches with lots of small commits (especially titled "oops", "fix typo", "forgot to add file", etc.) should be squashed before opening a pull request. At the same time, please refrain from putting multiple unrelated changes into a single pull request.

### License and credits ###

Arduino IDE is developed and maintained by the Arduino team. The IDE is licensed under GPL.

ESP8266 core includes an xtensa gcc toolchain, which is also under GPL.

Esptool written by Christian Klippel is licensed under GPLv2, currently maintained by Ivan Grokhotkov: https://github.com/igrr/esptool-ck.

Espressif SDK included in this build is under Espressif MIT License.

ESP8266 core files are licensed under LGPL.

PubSubClient library written by Nick O'Leary is used in this project. It is distributed under MIT license.

[ArduinoJson](arduinojson.org) JSON parser library written by Benoit Blanchon is used in this project. It is distributed under MIT license.

