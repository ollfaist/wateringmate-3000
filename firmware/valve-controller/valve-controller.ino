#include "config_local.h"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Pin definitions
#define RELAY_PIN   D1   // GPIO5 — LOW = valve open (active low relay)
#define DHT_PIN     D5   // GPIO14
#define DHT_TYPE    DHT22

// Blynk virtual pins
#define VPIN_TEMP       V0
#define VPIN_HUMIDITY   V1
#define VPIN_VALVE      V2   // valve status (display)
#define VPIN_WATER_NOW  V3   // button: open valve until stopped
#define VPIN_DURATION   V4   // slider: minutes (1-60)
#define VPIN_WATER_TIMED V5  // button: water for selected duration

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

int waterDurationMinutes = 5;
bool valveOpen = false;
int timedWaterTimerId = -1;

void openValve() {
  digitalWrite(RELAY_PIN, LOW);
  valveOpen = true;
  Blynk.virtualWrite(VPIN_VALVE, 1);
}

void closeValve() {
  digitalWrite(RELAY_PIN, HIGH);
  valveOpen = false;
  Blynk.virtualWrite(VPIN_VALVE, 0);
  if (timedWaterTimerId != -1) {
    timer.deleteTimer(timedWaterTimerId);
    timedWaterTimerId = -1;
  }
}

// Water now button
BLYNK_WRITE(VPIN_WATER_NOW) {
  int val = param.asInt();
  if (val == 1) {
    openValve();
  } else {
    closeValve();
  }
}

// Duration slider (1-60 minutes)
BLYNK_WRITE(VPIN_DURATION) {
  waterDurationMinutes = param.asInt();
}

// Water for X minutes button
BLYNK_WRITE(VPIN_WATER_TIMED) {
  if (param.asInt() == 1) {
    openValve();
    timedWaterTimerId = timer.setTimeout(waterDurationMinutes * 60000L, closeValve);
  }
}

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) return;

  Blynk.virtualWrite(VPIN_TEMP,     temp);
  Blynk.virtualWrite(VPIN_HUMIDITY, hum);
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  closeValve();

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  // Send sensor data every 30 seconds
  timer.setInterval(30000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
