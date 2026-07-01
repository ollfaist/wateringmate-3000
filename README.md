# WateringMate 3000

Automated greenhouse watering system with two modules and a mobile app.

## Architecture

```
Mobil (Blynk-app)
       │
  [Blynk Cloud]
    ▲       ▲
    │       │
  ESP32   D1 Mini
(sensor) (ventil)
```

- **Blynk** hanterar UI, realtidsvärden, historik och styrning
- Ingen server, ingen VPN, fungerar var som helst via mobil

## Modules

### Greenhouse Node (ESP32)
Battery-powered sensor node inside the greenhouse.
- **MCU:** ESP32
- **Sensors:** DHT22 (air temp + humidity), Mi Flora via BLE (soil moisture, soil temp, light, nutrients)
- **Power:** 18650 + TP4056 USB-C charger + 10W solar panel
- **Battery monitor:** Voltage divider (100kΩ + 100kΩ) on GPIO34
- **Sends to Blynk:** Air temp, air humidity, soil moisture, soil temp, light, nutrients, battery %

### Valve Controller (D1 Mini)
Mains-powered controller at the house water outlet.
- **MCU:** Wemos D1 Mini
- **Sensor:** DHT22 (temperature + humidity)
- **Power:** 230VAC → BRIMETi 24VDC/1A + MP1584EN step-down → 5V
- **Output:** SRD-05VDC relay → 24VDC NC solenoid valve
- **Receives from Blynk:** Water now, water for X minutes
- **Sends to Blynk:** Valve status, local temp + humidity

## Blynk UI
- Gauges: air temp, air humidity, soil moisture, battery %
- Values: soil temp, light, nutrients
- Button: Water now
- Slider + button: Water for X minutes
- SuperChart: temp + humidity history

## Repository Structure

```
wateringmate-3000/
├── firmware/
│   ├── greenhouse-node/     # ESP32 firmware (Blynk + DHT22 + BLE Mi Flora)
│   └── valve-controller/    # D1 Mini firmware (Blynk + DHT22 + relay)
├── hardware/
│   ├── greenhouse-node/     # CAD files + STL for enclosure
│   └── valve-controller/    # CAD files + STL for enclosure
└── docs/
    └── schematics/          # Wiring diagrams
```
