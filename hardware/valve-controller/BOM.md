# BOM — Valve Controller

| # | Component         | Model / Notes                        | Dimensions        | Qty |
|---|-------------------|--------------------------------------|-------------------|-----|
| 1 | MCU               | Wemos D1 Mini (ESP8266)              | ~34 × 25mm        | 1   |
| 2 | Temp/Humidity     | DHT22                                | ~15 × 15mm        | 1   |
| 3 | AC/DC             | 230VAC → 24VDC                       | TBD               | 1   |
| 4 | Step-down         | MP1584EN (24V → 5V)                  | ~22 × 17mm        | 1   |
| 5 | Relay module      | SRD-05VDC-SL-C, 1ch, 5V, 10A/250VAC | ~50 × 26mm        | 1   |
| 6 | Valve             | 24VDC NC solenoid valve              | External           | 1   |

## Notes
- 230VAC input → AC/DC → 24VDC rail
- 24VDC → MP1584EN stepdown → 5V for D1 Mini + relay coil
- Relay NO/NC switches 24VDC to valve (NC = valve closed on power loss = safe default)
- Valve is external, connected via cable gland
- AC/DC and relay handle mains voltage — enclosure must be properly rated
