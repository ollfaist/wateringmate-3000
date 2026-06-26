# Layout Reference — Komponentmått (top-down)

## Greenhouse Node

| Komponent     | L (mm) | B (mm) | H (mm) | Notering                  |
|---------------|--------|--------|--------|---------------------------|
| ESP32 DevKit  | 55     | 28     | 10     | USB på kortsidan          |
| TP4056 USB-C  | 28     | 17     | 4      | USB-C på kortsidan        |
| 18650 batteri | 65     | 18     | 18     | Cylindrisk ø18            |
| DHT22         | 43     | 15     | 13     | PCB genom vägg, huvud utanpå — hål 14×40mm |

**Föreslagen inre kapslingsstorlek: 90 × 40 × 30 mm**
- 18650 ligger längs med (65mm), ESP32 bredvid (28mm bred)
- TP4056 vid sidan av ESP32

---

## Valve Controller

| Komponent        | L (mm) | B (mm) | H (mm) | Notering                        |
|------------------|--------|--------|--------|---------------------------------|
| BRIMETi AC/DC    | 93     | 30     | 20     | Störst — styr kapslingslängden  |
| Relä SRD-05VDC   | 50     | 26     | 16     | Inkl. reläkropp                 |
| MP1584EN         | 22     | 17     | 8      |                                 |
| D1 Mini          | 34     | 25     | 10     | USB på kortsidan                |
| DHT22            | 43     | 15     | 13     | PCB genom vägg, huvud utanpå — hål 14×40mm |

**Föreslagen inre kapslingsstorlek: 120 × 60 × 40 mm**
- AC/DC längs med (93mm) tar hela längden
- Relä, D1 Mini, MP1584 staplas/grupperas bredvid

---

## Kapslingsväggar
- Väggtjocklek rekommenderat: **2.5 mm** (PETG/ASA)
- Skruvbossar: M3, höjd 5 mm, ytterdiameter 6 mm
- Kabelgenomföringar: PG7 (max ø8mm kabel)
- DHT22-öppning: 14 × 40 mm (PCB går igenom, sensorhuvud 15mm fungerar som stopp utifrån)

## Tips monteringsordning (Valve Controller)
```
[AC/DC 93×30] | [Relä 50×26]
               | [D1 Mini 34×25]
               | [MP1584 22×17]
```
