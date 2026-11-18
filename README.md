# Industrial Temperature Monitor Using ESP32 and DHT22

## 📌 Project Overview

This project implements an Industrial Temperature Monitoring System using an ESP32, DHT22 temperature and humidity sensor, push button, and LED.

The system measures temperature and humidity using the DHT22 sensor and publishes the collected data to an MQTT broker over Wi-Fi every 2 seconds.

A push button is used for local emergency fan control. The LED represents the cooling fan and can be manually turned ON or OFF using the push button.

The system continues to support local button and fan operation even when Wi-Fi is disconnected.

## 🎯 Objectives

- Monitor temperature and humidity using the DHT22 sensor.
- Use ESP32 for sensor data processing.
- Connect to Wi-Fi using the Wokwi-GUEST network.
- Publish temperature and humidity data to an MQTT broker.
- Send sensor data every 2 seconds.
- Control the simulated cooling fan using a push button.
- Ensure local fan control works without Wi-Fi.
- Use non-blocking programming with the `millis()` function.

## 🛠️ Components Required

- ESP32 Development Board
- DHT22 Temperature and Humidity Sensor
- 1 × Push Button
- 1 × LED (Simulated Cooling Fan)
- 1 × 220Ω Resistor
- 1 × 10kΩ Resistor
- Jumper Wires

## 🔌 Pin Configuration

| Component | ESP32 Pin |
|---|---|
| DHT22 DATA | GPIO 4 |
| Push Button | GPIO 18 |
| LED (Fan) | GPIO 23 |
| DHT22 VCC | 3V3 |
| DHT22 GND | GND |
| LED Cathode | GND |

## ⚙️ Working Principle

1. The DHT22 sensor measures temperature and humidity.
2. The ESP32 reads sensor data every 2 seconds.
3. The ESP32 connects to the Wi-Fi network using the Wokwi-GUEST network.
4. Sensor data is published to the MQTT broker using the MQTT protocol.
5. The push button is used to manually control the simulated cooling fan.
6. When the button is pressed, the LED turns ON or OFF.
7. Local button and LED operation continue even if Wi-Fi is disconnected.
8. The `millis()` function is used for non-blocking timing.
9. The system automatically attempts to reconnect to Wi-Fi and MQTT when disconnected.

## 🌐 Wi-Fi and MQTT Configuration

| Parameter | Value |
|---|---|
| Wi-Fi SSID | Wokwi-GUEST |
| MQTT Broker | broker.hivemq.com |
| MQTT Port | 1883 |
| MQTT Topic | industrial/monitor/temperature |
| Data Publishing Interval | 2 Seconds |

### Sample MQTT Data

```json
{
  "temperature": 24.0,
  "humidity": 40.0
}
```

## 💻 Source Code

The complete ESP32 source code is available in:

- `sketch.ino`

### Required Libraries

- DHT sensor library
- Adafruit Unified Sensor
- PubSubClient

## 🔗 Simulation Links

- **Wokwi Simulation:**https://wokwi.com/projects/481025584390577153 
  

## 📚 Technologies and Concepts Used

- ESP32 Microcontroller
- DHT22 Sensor
- Wi-Fi Communication
- MQTT Protocol
- GPIO Input and Output
- Push Button Control
- Non-blocking Programming
- `millis()` Function

## 👩‍💻 Project Information

| Category | Details |
|---|---|
| Project Name | Industrial Temperature Monitor |
| Platform | ESP32 |
| Simulator | Wokwi |
| Programming Language | C++ |
| Communication Protocol | MQTT |
| Sensor | DHT22 |
| Project Type | IoT / Embedded Systems |

## 📝 Conclusion

This project demonstrates an IoT-based temperature and humidity monitoring system using ESP32 and DHT22. It provides practical experience with sensor interfacing, Wi-Fi communication, MQTT data publishing, GPIO control, and non-blocking programming.

The push button provides local control of the simulated cooling fan, allowing the system to maintain basic local operation even without an internet connection.

---

**Developed as part of an IoT and Embedded Systems Project.**
