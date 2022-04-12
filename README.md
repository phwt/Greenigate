# Greenigate

## Introduction
**Greenigate** is an IoT automation solution for plant lovers that allows for remote watering and scheduling using humidity sensors to prevent both overwatering and underwatering. All of this is accessible via a mobile application.

สำหรับ **Greenigate** นี้เป็นระบบที่จะมาเป็นตัวช่วยในการดูแลจัดการต้นไม้ ทั้งในด้านการรดน้ำโดยอัตโนมัติแบบกำหนดเวลา, รดน้ำโดยการสั่งการระยะไกล หรือตรวจวัดความชื้นของดินไม่ให้ชื้นเกินไป โดยทั้งหมดนี้สามารถสั่งการผ่านแอพพลิเคชั่นได้ทั้งหมด

## Features

- Automatic watering scheduling
  - Configurable water volume
  - Prevent overwatering when humidity exceeds 70%
- Warning notification for overwatering/underwatering
  - Configurable humidity range
- Remotely accessible via a mobile application
- Simple network setup without source code modification

---

- รดน้ำอัตโนมัติตามเวลาที่ได้ตั้งไว้
  - สามารถปรับปริมาณน้ำได้
  - หากความชื้นวัดได้เกิน 70% จะไม่ทำการรดให้
- แจ้งเตือนความชื้นมาก/น้อยเกิน
  - สามารถปรับขอบเขตความชื้นที่ต้องการได้
- ทุกอย่างควบคุมได้ผ่านทางแอพพลิเคชั่น
- รองรับการเปลี่ยนเครือข่าย โดยไม่ต้องแก้ไข Source Code โดยตรง

## Media

[![YouTube](https://raw.githubusercontent.com/phwt/Greenigate/master/media/youube-play.jpg "YouTube video")](https://youtu.be/gLr9KiQcmJc)

### - **Poster [[.ai](https://github.com/phwt/Greenigate/blob/master/media/ai/poster_print.ai) / [.pdf](https://github.com/phwt/Greenigate/blob/master/media/ai/poster_print.pdf)]**

## How to use

การติดตั้ง, ตั้งค่าและใช้งานระบบนั้นสามารถดูได้ที่ **[YouTube - Greenigate](https://youtu.be/gLr9KiQcmJc)**

### การติดตั้งส่วน Blynk

สามารถทำการสแกน QR Code นี้ผ่านแอพฯ Blynk เพื่อติดตั้งส่วนควบคุม Greenigate ผ่านแอพฯ

![QR Code](https://raw.githubusercontent.com/phwt/Greenigate/master/media/bqr.png)

## Prerequisite

- `ESP8266` or equivalent
  - Soil Humidity Sensor x1
  - 3V DC Water Pump x1
  - Push Button x1
  - IRF520N MOSFET x1
  - 1N4004 Diode x1
  - LED x1
  - 220Ω Resistor x1
- `Blynk` [[Android](https://play.google.com/store/apps/details?id=cc.blynk) / [iOS](https://itunes.apple.com/us/app/blynk-iot-for-arduino-esp32/id808760481?mt=8)]

## Built-With

- `NodeMCU V2` - ESP8266 ESP12E
  - `WiFiManager` library
- `Blynk`
