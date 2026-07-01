# Blynk Setup — WateringMate 3000

## Skapa två templates på blynk.cloud

---

### Template 1: WateringMate-Valve
**Hardware:** ESP8266  

#### Datastreams
| Virtual Pin | Namn                  | Type    | Min | Max | Unit   |
|-------------|----------------------|---------|-----|-----|--------|
| V0          | Utetemp              | Double  | -30 | 60  | °C     |
| V1          | Uteluftfuktighet     | Double  | 0   | 100 | %      |
| V2          | Ventilstatus         | Integer | 0   | 1   |        |
| V3          | Vattna nu            | Integer | 0   | 1   |        |
| V4          | Vattnatid            | Integer | 1   | 60  | min    |
| V5          | Vattna X min         | Integer | 0   | 1   |        |

#### Dashboard widgets
- **Label** → Utetemp (V0), Uteluftfuktighet (V1)
- **LED** → Ventilstatus (V2)
- **Button** Switch → Vattna nu (V3)
- **Slider** → Vattnatid 1-60 min (V4)
- **Button** Push → Vattna X min (V5)
- **SuperChart** → Utetemp + Uteluftfuktighet

---

### Template 2: WateringMate-Greenhouse
**Hardware:** ESP32  

#### Datastreams
| Virtual Pin | Namn                      | Type    | Min    | Max    | Unit   |
|-------------|--------------------------|---------|--------|--------|--------|
| V6          | Växthustemperatur (luft) | Double  | -20    | 60     | °C     |
| V7          | Växthusluftfuktighet     | Double  | 0      | 100    | %      |
| V8          | Jordfuktighet            | Integer | 0      | 100    | %      |
| V9          | Jordtemperatur           | Double  | -20    | 60     | °C     |
| V10         | Ljus                     | Integer | 0      | 100000 | lux    |
| V11         | Näring                   | Integer | 0      | 2000   | uS/cm  |
| V12         | Batteri                  | Double  | 0      | 100    | %      |

#### Dashboard widgets
- **Gauge** → Jordfuktighet (V8), Batteri (V12)
- **Label** → Växthustemperatur, Växthusluftfuktighet, Jordtemperatur, Ljus, Näring
- **SuperChart** → Växthustemperatur + Växthusluftfuktighet + Jordtemperatur

---

## Temperaturer i systemet
Tre temperaturer finns tillgängliga att jämföra:
- **Utetemp** (V0) — DHT22 vid ventilen utomhus
- **Växthustemperatur** (V6) — DHT22 inne i växthuset
- **Jordtemperatur** (V9) — Mi Flora i jorden

---

## Credentials i firmware
När device är skapat, kopiera till `config_local.h`:
```cpp
#define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "WateringMate-Valve"   // eller Greenhouse
#define BLYNK_AUTH_TOKEN    "xxxxxxxxxxxxxxxxxxxxxx"
```
