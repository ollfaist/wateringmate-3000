# BOM — Greenhouse Node

| # | Component         | Model / Notes                        | Dimensions        | Qty |
|---|-------------------|--------------------------------------|-------------------|-----|
| 1 | MCU               | ESP32 DevKit (38-pin)                | ~55 × 28mm        | 1   |
| 2 | Temp/Humidity     | DHT22                                | ~15 × 15mm        | 1   |
| 3 | Battery           | 18650 Li-Ion                         | ø18 × 65mm        | 1   |
| 4 | Charger           | TP4056 + DW01A, USB-C                | 28 × 17mm         | 1   |

## Notes
- Charger input: USB-C 5V
- Battery output protected via DW01A (overcurrent/overdischarge)
- ESP32 powered from battery OUT+ via charger board
