# M5Stack Env3 Harvest

This sample shows how to send humidity and temperature, pressure from Env III to harvest.

- [ENV III Unit with Temperature Humidity Air Pressure Sensor (SHT30+QMP6988)](https://shop.m5stack.com/products/env-iii-unit-with-temperature-humidity-air-pressure-sensor-sht30-qmp6988)
- [M5Stack Basic](https://m5stack.com/)
- [M5Stack 3G Module](https://soracom.jp/store/5231/)
- Soracom SIM

## Prerequisite

### Enable Soracom harvest

Enable Soracom Harvest feature by following the [doument abount the Harvest](https://users.soracom.io/ja-jp/docs/harvest/send-data/)

### Setup ArduinoIDE

Setup Arduino to use M5Stack by following the document [setup-for-m5stack-with-arduino-ide](https://soracom.github.io/iot-recipes/setup-for-m5stack-with-arduino-ide)

### Setup ArduinoIDE

Install the following libraries to your Arduino IDE

- [M5Stack:0.3.9](https://github.com/m5stack/m5stack)
- [UNIT_ENV:0.0.2](https://github.com/m5stack/UNIT_ENV/releases/tag/0.0.2)
- [TinyGSM:0.11.5](https://github.com/vshymanskyy/TinyGSM)
- [ArduinoHTTPClient:0.4.0](https://github.com/arduino-libraries/ArduinoHttpClient)
- [ArduinoJson6.19.3](https://github.com/bblanchon/ArduinoJson)

## Compile and Run

With your Arduino IDE, compile [sketch_harvest_humidtemp.ino](./sketch_harvest_humidtemp.ino)
