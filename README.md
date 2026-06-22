# Smart Room Automation System

An IoT-based smart room automation system that monitors temperature, humidity, and motion in real time, then automatically controls room lighting and a fan.

The system uses an **ESP8266 NodeMCU**, **DHT11 temperature and humidity sensor**, **PIR motion sensor**, **relay module**, **LED light**, and the **Blynk IoT platform** for live monitoring and manual control.

![Blynk Dashboard](media/blynk-dashboard.png)

## Overview

Traditional rooms often waste energy because lights and fans can remain ON even when no one is present. This project solves that problem by using sensor data to make automatic control decisions.

- If motion is detected, the LED light turns ON.
- If temperature exceeds **26°C**, the fan turns ON through the relay module.
- Temperature, humidity, motion, fan status, and light status are displayed in the Blynk dashboard.
- Manual fan and light controls are available through Blynk toggles.

## Features

- Real-time temperature monitoring
- Real-time humidity monitoring
- Motion-based lighting using PIR sensor
- Temperature-based fan automation
- Remote monitoring through Blynk IoT
- Manual fan and light override
- Low-cost smart room automation prototype

## Hardware Components

| Component | Purpose |
|---|---|
| ESP8266 NodeMCU | Main microcontroller with built-in Wi-Fi |
| DHT11 sensor | Measures temperature and humidity |
| PIR HC-SR501 sensor | Detects motion / human presence |
| Relay module | Switches the fan ON/OFF |
| LED light | Represents room lighting |
| 220Ω resistor | Protects the LED |
| Jumper wires / perfboard | Circuit connection and assembly |

## Software and Libraries

- Arduino IDE
- Blynk IoT platform
- ESP8266WiFi library
- BlynkSimpleEsp8266 library
- DHT sensor library

## Pin Connections

| Component | Component Pin | ESP8266 NodeMCU Pin |
|---|---:|---:|
| DHT11 | VCC | 3.3V |
| DHT11 | GND | GND |
| DHT11 | DATA | D4 |
| PIR Sensor | VCC | 3.3V |
| PIR Sensor | GND | GND |
| PIR Sensor | OUT | D6 |
| LED | Anode (+) | D1 through 220Ω resistor |
| LED | Cathode (-) | GND |
| Relay Module | VCC | 3.3V / 5V depending on module |
| Relay Module | GND | GND |
| Relay Module | IN | D8 |

## Blynk Virtual Pins

| Virtual Pin | Widget | Description |
|---|---|---|
| V0 | Gauge | Temperature reading in °C |
| V1 | Gauge | Humidity reading in % |
| V2 | LED Indicator | Motion status |
| V3 | LED Indicator | Fan status |
| V4 | LED Indicator | Light status |
| V5 | Button Toggle | Manual fan control |
| V6 | Button Toggle | Manual light control |

## Automation Logic

```text
Light control:
IF motion is detected OR manual light toggle is ON
    LED turns ON
ELSE
    LED turns OFF

Fan control:
IF temperature > 26°C OR manual fan toggle is ON
    Fan turns ON through relay
ELSE
    Fan turns OFF
```

## Project Photos

### Prototype
![Prototype](media/prototype-clean.png)

### Building and Testing
![Building the Project](media/building-the-project.jpeg)

### Project Presentation
![Project Presentation](media/project-presentation.jpeg)

## How to Run

1. Install the Arduino IDE.
2. Install the ESP8266 board package.
3. Install the required libraries:
   - Blynk
   - DHT sensor library
   - Adafruit Unified Sensor
4. Create a Blynk IoT template and dashboard.
5. Add the virtual pins V0 to V6 in Blynk.
6. Open `src/SmartRoomAutomation.ino`.
7. Replace these placeholders with your own values:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
```

8. Select the ESP8266 NodeMCU board in Arduino IDE.
9. Upload the code to the board.
10. Open the Blynk dashboard and monitor the live data.

## Results

The system was tested successfully:

- The LED turned ON when motion was detected.
- The fan turned ON when the temperature exceeded 26°C.
- The Blynk dashboard displayed temperature, humidity, motion status, fan status, and light status.
- Manual fan and light toggles worked from the Blynk app.

## Future Improvements

- Add voice control using Google Assistant or Alexa.
- Add energy consumption monitoring.
- Add temperature threshold control from the Blynk app.
- Add push notifications for high temperature alerts.
- Expand the system to support multiple rooms.

## License

This project is released under the MIT License.
