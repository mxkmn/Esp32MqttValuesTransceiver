# ESP32 MQTT analog values transceiver

## Description (English)

This project allows to transmit data received from analog pins of ESP32 via MQTT 3.1.1. It is optimised for classic ESP32: it allows to work in two modes (checks 6 or 13 pins) due to platform limitations. 

The code can be easily modified for other platforms (ESP32-S2, ESP32-C3), to transmit some other data (e.g. readings from digital pins or connected sensors).

The project was created in PlatformIO, to use it in Arduino IDE you have to download the library https://github.com/OttoWinter/pubsubclient. Additional changes may be needed due to the use of classes instead of normal .ino files.

## Description (Русский)

Этот проект позволяет передавать данные, полученные с аналоговых пинов ESP32, через протокол MQTT 3.1.1. Он оптимизирован для классической ESP32: позволяет работать в двух режимах (опрос 6 или 13 пинов) в связи с ограничениями платформы. 

Код может быть с лёгкостью изменён под другие платформы (ESP32-S2, ESP32-C3), передавать какие-то другие данные (например показатели с цифровых пинов или подключённых сенсоров).

Проект создан в PlatformIO, для использования в Arduino IDE придётся загрузить библиотеку https://github.com/OttoWinter/pubsubclient. Возможно понадобятся дополнительные изменения в связи с использованием классов вместо обычных .ino файлов.