# Źródła do reverse engineeringu

Sklonowane jako git submodules w `vendor/` (shallow `--depth 1`):

| Repo | Po co |
| --- | --- |
| [evil-mad/axidraw](https://github.com/evil-mad/axidraw) | Plugin Inkscape (`inkscape driver/`), CLI, Python API |
| [evil-mad/plotink](https://github.com/evil-mad/plotink) | `ebb_serial.py`, `ebb_motion.py` — jedyne miejsce detekcji USB i komend ruchu |
| [evil-mad/EggBot](https://github.com/evil-mad/EggBot) | Firmware PIC (`EBB_firmware/app.X`), HEX-e, INF Windows |

Lokalne zrzuty w `docs/upstream/`:

| Plik | Źródło |
| --- | --- |
| `ebb-command-set.html` / `.md` | https://evil-mad.github.io/EggBot/ebb.html |
| `EiBotBoard-v26_sch.pdf` / `_brd.pdf` | https://www.schmalzhaus.com/EBB/ |
| `EiBotBoard-v27_sch.pdf` / `_brd.pdf` | to samo, najnowsza publiczna rewizja |
| `EBB-index.html` `EBBHistory.html` | historia: PIC18F46J50, A3967 → A4983 |
| `Updating_EBB_firmware.html` | wiki EMSL |
| `Axidraw_Software_Installation.html` | instalacja pluginu |

Sprzęt oryginału (Schmalz Haus / EMSL, CC-BY na plikach Eagle):

- CPU: PIC18F46J50-I/PT
- Sterowniki: 2× Allegro A4983 (v1.2+), prąd 46 mA–1,25 A trimpotem
- USB Microchip VID `04D8` PID `FD92`
- Wejście 6–24 V, 5 V serwo, 3,3 V MCU
- Serwo pióra: RB1
- Przycisk PRG: pauza plotu

Firmware EBB **nie** jest w repo AxiDraw — tylko w EggBot. MLA (stos USB Microchip) nie wolno redystrybuować; w `EBB_firmware/Microchip` go nie ma.
