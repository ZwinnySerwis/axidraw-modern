# Plan gry (zablokowany 2026-10-10)

Cel: ploter kompatybilny z **oryginalnym pluginem Inkscape AxiDraw**, nowa płyta od zera, **stepsticki**, MCU **RP2040**.

## Zasada MVP

Nie forujemy UI. Host zostaje. Firmware mówi protokołem EBB. Plugin ma „widzieć EiBotBoard”.

```
Inkscape (stock) → plotink USB CDC → nasze firmware → 2× stepstick + serwo
```

## Sprzęt, który już jest

- Raspberry Pi Pico **RP2040, 264 kB SRAM** (klasyczne Pico) — to wystarczy z zapasem (PIC miał ~3,8 kB RAM).
- Stepsticki będą. Na pierwszy odpal: cokolwiek STEP/DIR (A4988 / DRV8825 / TMC legacy). TMC UART to etap po MVP.
- Płytka **od zera** w KiCad, nie Eagle-fork OEM.

## Fazy

### 0. Proto (ten Pico z półki, bez PCB)

1. Toolchain: ARM GCC + Pico SDK, blink + USB CDC.
2. USB `iProduct = EiBotBoard`, `V` → `EBBv13_and_above EBB Firmware Version 2.8.1`.
3. Parser EBB z `tools/ebb_sim` / `firmware/src/ebb_parser.c`: `EM SM XM SP SC QP QB QS QC PI QG SL QL CS ES`.
4. PIO albo timer: STEP/DIR według `hardware/PINOUT.md`.
5. Serwo PWM na GP15, przycisk GP14.
6. Test: Inkscape → Extensions → AxiDraw widzi urządzenie i rusza silnikami na proto.

Sukces fazy 0: jeden SVG z `vendor/axidraw/examples` narysowany na stole, **bez zmian pluginu**.

### 1. PCB rev A (KiCad, Pico jako moduł)

Nie chip-down na pierwszym spinie. Pico (castellated / socket) + dwa sockety 16-pin stepstick + VMOT 12–24 V + buck 5 V serwo + USB z Pico + pauza + dzielnik ADC.

Referencja elektryczna: Eagle OEM v2.7 (`docs/SCHEMATICS.md`), layout własny.

Dlaczego moduł, nie goły RP2040: USB 12 MHz + kwarc 12 MHz + flash QSPI to darmowy koszt na Pico. Chip-down = rev B, gdy proto i rev A już plotują.

### 2. Firmware twardy

FIFO ruchu (OK przy przyjęciu komendy, nie po ruchu), limit 25 k kroków/s, `XM` = A±B, `PI` udaje piny enable/MS (plugin tak czyta mikrokrorki), `QC` napięcie > 250.

### 3. Świadomie później

TMC UART / prąd z komend, Wi‑Fi (inny MCU albo mostek), fork pluginu, goły RP2040 na PCB, trzecia oś.

## Decyzje zamknięte

- MCU: RP2040 (Pico 264 kB), nie ESP32, nie STM32, nie PIC na nowej płycie.
- Host MVP: stock AxiDraw plugin.
- USB: nazwa `EiBotBoard`, VID Raspberry Pi — bez podszywania się pod `04D8:FD92`.
- CAD: KiCad.
- PCB rev A: Pico module + 2× stepstick.
- Licencja drzewa: GPL-2.0.
