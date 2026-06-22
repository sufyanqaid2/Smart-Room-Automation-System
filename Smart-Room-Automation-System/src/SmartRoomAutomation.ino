/**************************************************************
  Smart Room Automation System
  Board: ESP8266 NodeMCU
  Platform: Arduino IDE + Blynk IoT

  Features:
  - Reads temperature and humidity using DHT11
  - Detects motion using PIR sensor
  - Automatically turns fan ON when temperature exceeds threshold
  - Automatically turns LED ON when motion is detected
  - Sends live data to Blynk dashboard
  - Allows manual fan/light override from Blynk

  Security note:
  Replace the placeholders below with your own Blynk and Wi-Fi data.
  Do not upload real passwords or tokens to a public GitHub repository.
**************************************************************/

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Room Automation System"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Wi-Fi credentials
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Pin definitions for ESP8266 NodeMCU
#define DHTPIN D4
#define DHTTYPE DHT11
#define PIR_PIN D6
#define LED_PIN D1
#define RELAY_PIN D8

// Blynk virtual pins
#define VPIN_TEMPERATURE V0
#define VPIN_HUMIDITY    V1
#define VPIN_MOTION      V2
#define VPIN_FAN_STATUS  V3
#define VPIN_LIGHT_STATUS V4
#define VPIN_MANUAL_FAN  V5
#define VPIN_MANUAL_LIGHT V6

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

float tempThreshold = 26.0;
int manualFan = 0;
int manualLight = 0;

// Change this to true if your relay module turns ON when the pin is LOW
const bool RELAY_ACTIVE_LOW = false;

void setFan(bool state) {
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(RELAY_PIN, state ? LOW : HIGH);
  } else {
    digitalWrite(RELAY_PIN, state ? HIGH : LOW);
  }
}

BLYNK_WRITE(VPIN_MANUAL_FAN) {
  manualFan = param.asInt();
}

BLYNK_WRITE(VPIN_MANUAL_LIGHT) {
  manualLight = param.asInt();
}

void sendSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int motion = digitalRead(PIR_PIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 reading error");
    return;
  }

  bool lightOn = (motion == HIGH) || (manualLight == 1);
  bool fanOn = (temperature > tempThreshold) || (manualFan == 1);

  digitalWrite(LED_PIN, lightOn ? HIGH : LOW);
  setFan(fanOn);

  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature);
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity);
  Blynk.virtualWrite(VPIN_MOTION, motion);
  Blynk.virtualWrite(VPIN_FAN_STATUS, fanOn ? 1 : 0);
  Blynk.virtualWrite(VPIN_LIGHT_STATUS, lightOn ? 1 : 0);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Motion: ");
  Serial.print(motion);
  Serial.print(" | Fan: ");
  Serial.print(fanOn ? "ON" : "OFF");
  Serial.print(" | Light: ");
  Serial.println(lightOn ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  setFan(false);

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
