# Sample code for M5Stack + Env III sensor to send data to Soracom Harvest

This sample shows how to send temperature, humidity and atmospheric pressure data captured using M5Stack and Env III sensor to Soracom Harvest.

- [ENV III Unit with Temperature Humidity Air Pressure Sensor (SHT30+QMP6988)](https://shop.m5stack.com/products/env-iii-unit-with-temperature-humidity-air-pressure-sensor-sht30-qmp6988)
- [M5Stack Basic](https://m5stack.com/)
- [M5Stack 3G Module](https://soracom.jp/store/5231/)
- SORACOM IoT SIM

## Prerequisites

### Enable Soracom Harvest

Enable Soracom Harvest feature by following [the steps described in the document](https://users.soracom.io/ja-jp/docs/harvest/send-data/).

### Setup Arduino IDE

Setup Arduino IDE to use M5Stack by following the steps described in the document [setup-for-m5stack-with-arduino-ide](https://soracom.github.io/iot-recipes/setup-for-m5stack-with-arduino-ide). Please make sure your Arduino IDE targets `M5Stack-Core-ESP32` as the board configuration.

### Install dependencies

Install the following libraries to your Arduino IDE

- [M5Stack:0.3.9](https://github.com/m5stack/m5stack)
- [UNIT_ENV:0.0.2](https://github.com/m5stack/UNIT_ENV/releases/tag/0.0.2)
- [TinyGSM:0.11.5](https://github.com/vshymanskyy/TinyGSM)
- [ArduinoHTTPClient:0.4.0](https://github.com/arduino-libraries/ArduinoHttpClient)
- [ArduinoJson6.19.3](https://github.com/bblanchon/ArduinoJson)

## Compile and Run

With your Arduino IDE, compile and run [the sketch](./m5stack-env3-harvest-sample.ino)
