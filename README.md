# WateringMate 3000

Automated greenhouse watering system with two modules.

## Modules

### Greenhouse Node
Battery-powered sensor node inside the greenhouse.
- **MCU:** ESP32
- **Sensor:** DHT22 (temperature + humidity)
- **Power:** 18650 + charging board

### Valve Controller
Mains-powered controller at the house water outlet.
- **MCU:** Wemos D1 Mini
- **Sensor:** DHT22 (temperature + humidity)
- **Power:** 230VAC → 24VDC AC/DC + step-down to 5V
- **Output:** Relay → 24VDC NC solenoid valve

## Repository Structure

```
wateringmate-3000/
├── firmware/
│   ├── greenhouse-node/     # ESP32 firmware
│   └── valve-controller/    # D1 Mini firmware
├── hardware/
│   ├── greenhouse-node/     # CAD files + STL for enclosure
│   └── valve-controller/    # CAD files + STL for enclosure
└── docs/
    └── schematics/          # Wiring diagrams
```
