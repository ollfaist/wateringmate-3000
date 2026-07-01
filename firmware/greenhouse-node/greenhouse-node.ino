#include "config_local.h"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <BLEDevice.h>
#include <BLEClient.h>

// Pin definitions
#define DHT_PIN         4    // GPIO4
#define DHT_TYPE        DHT22
#define BATTERY_PIN     34   // GPIO34 — voltage divider (100k + 100k)

// Deep sleep interval
#define SLEEP_MINUTES   15
#define uS_TO_MIN       60000000ULL

// Blynk virtual pins
#define VPIN_AIR_TEMP       V6
#define VPIN_AIR_HUM        V7
#define VPIN_SOIL_MOISTURE  V8
#define VPIN_SOIL_TEMP      V9
#define VPIN_LIGHT          V10
#define VPIN_NUTRIENTS      V11
#define VPIN_BATTERY        V12

// Mi Flora BLE UUIDs
static BLEUUID serviceUUID("00001204-0000-1000-8000-00805f9b34fb");
static BLEUUID dataUUID("00001a01-0000-1000-8000-00805f9b34fb");
static BLEUUID modeUUID("00001a00-0000-1000-8000-00805f9b34fb");

DHT dht(DHT_PIN, DHT_TYPE);

struct MiFloraData {
  float  soilTemp;
  int    moisture;
  int    light;
  int    conductivity;
  bool   valid = false;
};

// ── Battery ──────────────────────────────────────────────────────────────────

float readBatteryPercent() {
  int raw = analogRead(BATTERY_PIN);
  float voltage = (raw / 4095.0) * 3.3 * 2.0;  // x2 for voltage divider
  float pct = (voltage - 3.0) / (4.2 - 3.0) * 100.0;
  return constrain(pct, 0.0, 100.0);
}

// ── Mi Flora BLE ──────────────────────────────────────────────────────────────

MiFloraData readMiFlora() {
  MiFloraData data;

  BLEDevice::init("");
  BLEClient* client = BLEDevice::createClient();

  BLEAddress addr(MIFLORA_MAC);
  if (!client->connect(addr)) {
    Serial.println("Mi Flora: anslutning misslyckades");
    BLEDevice::deinit(true);
    return data;
  }

  BLERemoteService* svc = client->getService(serviceUUID);
  if (!svc) {
    client->disconnect();
    BLEDevice::deinit(true);
    return data;
  }

  // Aktivera realtidsläsning
  BLERemoteCharacteristic* mode = svc->getCharacteristic(modeUUID);
  if (mode) {
    uint8_t enable[] = {0xA0, 0x1F};
    mode->writeValue(enable, sizeof(enable), true);
  }

  delay(500);

  BLERemoteCharacteristic* dataChar = svc->getCharacteristic(dataUUID);
  if (!dataChar) {
    client->disconnect();
    BLEDevice::deinit(true);
    return data;
  }

  std::string raw = dataChar->readValue();
  if (raw.size() < 8) {
    client->disconnect();
    BLEDevice::deinit(true);
    return data;
  }

  const uint8_t* b = (const uint8_t*)raw.data();
  data.soilTemp    = ((b[1] << 8) | b[0]) / 10.0;
  data.moisture    = b[7];
  data.light       = (b[4] << 8) | b[3];
  data.conductivity= (b[9] << 8) | b[8];
  data.valid       = true;

  client->disconnect();
  BLEDevice::deinit(true);
  return data;
}

// ── Main ──────────────────────────────────────────────────────────────────────

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Läs DHT22
  delay(2000);
  float airTemp = dht.readTemperature();
  float airHum  = dht.readHumidity();

  // Läs batteri
  float battery = readBatteryPercent();

  // Läs Mi Flora via BLE
  MiFloraData flora = readMiFlora();

  // Koppla upp WiFi + Blynk och skicka data
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  if (!isnan(airTemp)) Blynk.virtualWrite(VPIN_AIR_TEMP, airTemp);
  if (!isnan(airHum))  Blynk.virtualWrite(VPIN_AIR_HUM,  airHum);
  Blynk.virtualWrite(VPIN_BATTERY, battery);

  if (flora.valid) {
    Blynk.virtualWrite(VPIN_SOIL_MOISTURE, flora.moisture);
    Blynk.virtualWrite(VPIN_SOIL_TEMP,     flora.soilTemp);
    Blynk.virtualWrite(VPIN_LIGHT,         flora.light);
    Blynk.virtualWrite(VPIN_NUTRIENTS,     flora.conductivity);
  }

  Blynk.run();
  delay(1000);

  // Deep sleep tills nästa mätning
  Serial.printf("Sover i %d minuter...\n", SLEEP_MINUTES);
  esp_sleep_enable_timer_wakeup(SLEEP_MINUTES * uS_TO_MIN);
  esp_deep_sleep_start();
}

void loop() {
  // Används inte — deep sleep återstartar via setup()
}
