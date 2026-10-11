# Firmware axidraw-modern (RP2040)

USB CDC jako EiBotBoard (protokół EBB) → STEP/DIR na stepstickach.

## Kompilacja (ta maszyna)

Nie PlatformIO. Pico SDK + CMake + Ninja.

- Pico SDK: `C:\Users\ZS\pico-sdk` (`PICO_SDK_PATH`)
- ARM GCC: `C:\Users\ZS\arm-gnu-toolchain\bin`
- CMake + Ninja na PATH

```powershell
cd C:\Users\ZS\Projects\axidraw-modern\firmware
. .\env.ps1
cmake -S . -B build -G Ninja -DPICO_BOARD=pico
cmake --build build
```

Wychodzi `firmware/build/axidraw_modern.uf2` (gitignored).

Wgrywanie: BOOTSEL → dysk `RPI-RP2` → skopiować UF2. Pico wraca jako COM (zwykle COM7). `picotool` / 1200 baud na Windows bywa zawodne.

## Config — dwa miejsca

Firmware **nie** zna mm/s ani pola roboczego. Plugin liczy kroki i czas; Pico puszcza impulsy.

### 1. `firmware/include/config.h` (po zmianie: przebudowa + UF2)

| Makro | Teraz | Po co |
| --- | --- | --- |
| `MOTION_STEP_DIV` | `16` | MS niepodłączone = pełny krok. Po spięciu MS1–3 z 3V3 ustaw `1`. |
| `INVERT_DIR_M1` / `M2` | `0` | `1` odwraca kierunek tego silnika. |
| `SWAP_MOTORS` | `0` | `1` zamienia motor1 ↔ motor2 (osie native pluginu). |
| `MIN_STEP_US` | `40` | cap 25 kHz. Nie podnoś bez 1/16. |
| `STEP_PULSE_US` | `5` | szerokość impulsu STEP. |
| `DIR_SETUP_US` | `10` | pauza po zmianie DIR. |

Piny GPIO: `firmware/include/board_pins.h`, ściąga `hardware/PROTO-SCIEGA.html`.

### 2. Plugin Inkscape (bez przebudowy firmware)

Prędkość, przyspieszenie, serwo: **AxiDraw Control → Options**. Apply na Config **nie** rusza silników.

Pole i skala:

`C:\Users\ZS\AppData\Roaming\inkscape\extensions\axidraw_conf.py`

(kopia w `axidraw_deps\axidrawinternal\axidraw_conf.py` — zmień obie, jeśli nie wiesz która idzie w ruch.)

| Zmienna | Domyślnie | Sens |
| --- | --- | --- |
| `speed_pendown` / `speed_penup` | 25 / 75 | 1–100; GUI Inkscape nadpisuje |
| `x_travel_default` / `y_travel_default` | 11.81 / 8.58 in | pole V3 (~300×218 mm), `model = 1` |
| `native_res_factor` | 1016.0 | kroki/cal na osiach native (nie XY). 16T GT2 + 1/16 jak AxiDraw |
| `skip_voltage_check` | False | `True` jeśli `QC` straszy bez ADC |

Kinematyka AxiDraw (`XM`): silnik1/silnik2 to osie native `(X+Y)` / `(X−Y)`, nie czyste X i Y. Lustra na proto: `SWAP_MOTORS` i `INVERT_DIR_*` w `config.h`.

Stock plugin. Jedyny dopuszczalny patch hosta: VID `2E8A` w `findPort`.

## USB

- `iManufacturer`: `axidraw-modern`
- `iProduct`: `EiBotBoard`
- VID/PID: Raspberry Pi `2E8A:000A` — nie Microchip `04D8:FD92`
