# Handoff

## 2026-10-10

### For the next agent
Read this file first — **only the latest dated section** is current. Older sections are history. Then skim the files in **Read next**. Do not re-litigate closed decisions. Continue from **Next**.

### Goal
Nowoczesny kontroler plotera kompatybilny z stockowym pluginem Inkscape AxiDraw: firmware emuluje protokół EBB, płyta od zera ze stepstickami, MCU RP2040 (Pico 264 kB, które użytkownik już ma).

### Closed decisions
- Nie przenosimy tego czatu do repo — nowy Agent po File → Open Folder na `C:\Users\Kleszcz\Projects\axidraw-modern`.
- MCU: **RP2040 / Pico 264 kB SRAM**. ESP32 i STM32 odłożone. PIC tylko jako referencja OEM.
- MVP hosta: **bez forka pluginu**. USB `iProduct=EiBotBoard`, `V` z `Firmware Version 2.8.1`.
- Stepsticki native (gniazda), nie wlutowane A4983.
- PCB rev A: Pico jako moduł, nie chip-down. KiCad. OEM Eagle v2.7 tylko jako referencja elektryczna.
- Nie kopiujemy Microchip VID `04D8:FD92`.
- TMC UART, Wi‑Fi, fork UI — po MVP.

### Done
- Repo: https://github.com/ZwinnySerwis/axidraw-modern (`main`)
- Submoduły: `vendor/axidraw`, `vendor/plotink`, `vendor/EggBot`
- Emulator protokołu + 6 testów: `tools/ebb_sim`, `tests/`
- Szkielet firmware Pico: `firmware/`
- Pinout proto: `hardware/PINOUT.md`
- Eagle/PDF OEM v2.7: `docs/upstream/oem/EBB_v27/`
- Plan: `docs/PLAN.md`

### Next
1. Otworzyć ten folder w Cursorze, nowy Agent, `@HANDOFF.md`.
2. Faza 0 z `docs/PLAN.md`: toolchain Pico SDK + ARM GCC na Windows, USB CDC z nazwą EiBotBoard na Pico użytkownika.
3. Podłączyć dwa stepsticki wg `hardware/PINOUT.md`, dociągnąć `SM`/`XM`/`SP`/`EM` do prawdziwych GPIO/PIO.
4. Sprawdzić, że stockowy plugin (`host/install_inkscape_plugin.ps1`) widzi płytkę.
5. Dopiero potem KiCad rev A (nie wcześniej).

### Read next
- `docs/PLAN.md` — fazy i zasada MVP
- `docs/MCU.md` — uzasadnienie RP2040
- `docs/SCHEMATICS.md` — gdzie jest OEM PIC18F46J50
- `docs/ARCHITECTURE.md` — protokół vs host
- `docs/PROTOCOL.md` — komendy, których plugin naprawdę używa
- `hardware/PINOUT.md` — Pico ↔ stepstick
- `tools/ebb_sim/ebb_protocol.py` — złoty model odpowiedzi EBB

### Git
- Branch: `main`
- Last commit: `69cd3fc` Lock MVP plan, OEM Eagle v2.7, and handoff for the Pico proto phase.
- Remote: pushed — https://github.com/ZwinnySerwis/axidraw-modern

### Paste prompt
> Przeczytaj @HANDOFF.md — tylko najnowszy wpis (ostatni, z datą) jest aktualny; starsze to historia. Potem otwórz pliki z sekcji Read next i krótko potwierdź, że rozumiesz stan. Nie powtarzaj zamkniętych decyzji. Zaczynamy od: faza 0 z docs/PLAN.md — toolchain Pico SDK/ARM GCC, USB CDC jako EiBotBoard na Pico 264 kB, potem STEP/DIR na proto według hardware/PINOUT.md. PCB KiCad dopiero po tym, jak plugin zobaczy urządzenie.

---

## 2026-10-11

### For the next agent
Read this file first — **only the latest dated section** is current. Older sections are history. Then skim the files in **Read next**. Do not re-litigate closed decisions. Continue from **Next**.

### Goal
Nowoczesny kontroler plotera kompatybilny ze stockowym pluginem Inkscape AxiDraw. Firmware emuluje EBB na RP2040 (Pico 264 kB). Proto na stole, potem PCB rev A w KiCad.

### Closed decisions
- MCU: Pico RP2040 264 kB. Host MVP: stock plugin, `iProduct=EiBotBoard`, VID Raspberry Pi (nie `04D8:FD92`).
- Wgrywanie: Pico SDK + CMake + Ninja + UF2 / picotool. **Nie PlatformIO** (GCC 7.2 za stary).
- Trzy stepsticki na rev A: stick 3 = slave osi 2 (wspólne STEP/DIR GP5/GP6, EN na GP13). Nie równoległe cewki na jeden driver.
- Proto: DRV8825 z półki. Docelowo **TMC2209** (UART GP8/GP9 później).
- AS5600 ma stały adres `0x36`; zmiana adresu to **AS5600L**. Dwa I2C zostają (I2C0 GP0/1, I2C1 GP26/27).
- LSM6DS3TR-C na SPI0 (GP16–19) + INT1 GP22 — input shaping później, nie w pętli EBB.
- ADC VMOT: **GP28** (ADC2), nie GP26.
- KiCad dopiero gdy stockowy plugin zobaczy urządzenie.
- Enkodery/IMU/shaping: footprinty DNP na rev A, sterowników nie pisać bez chipów na stole.

### Done
- Toolchain na Windows: ARM GCC 14.2, Pico SDK 2.1.1 (`C:\Users\Kleszcz\pico-sdk`), picotool 2.1.1 (`C:\Users\Kleszcz\pico-tools`). `PICO_SDK_PATH` w zmiennych użytkownika. Sesja: `firmware/env.ps1`.
- UF2 zbudowany: `firmware/build/axidraw_modern.uf2` (gitignored). USB `EiBotBoard`, `V` → `Firmware Version 2.8.1`, LED miga. Parser EBB na CDC; **brak impulsów STEP/DIR**.
- Pinout zamknięty: `hardware/PINOUT.md`, `firmware/include/board_pins.h`.
- Ściąga do druku: `hardware/PROTO-SCIEGA.html` (A4 poziomo, Ctrl+P).
- Plan zaktualizowany: `docs/PLAN.md`.

### Next
1. Użytkownik w pracowni: BOOTSEL, skopiować `firmware/build/axidraw_modern.uf2` na `RPI-RP2`. LED ma migać.
2. Sprawdzić, że stockowy plugin (`host/install_inkscape_plugin.ps1`) widzi `EiBotBoard` i `V` wraca EBB 2.8.1. Jeśli Windows pokaże „USB Serial Device”, deskryptor / ewentualnie jedyny dopuszczalny patch `findPort`.
3. Proto: DRV8825 × 2–3 wg `hardware/PINOUT.md` / ściągi. PIO lub timer: `SM`/`XM` → STEP/DIR. EN active-low. Stick 3: STEP/DIR z osi 2.
4. Serwo GP15, pauza GP14, `QC` z ADC GP28 (na razie emulator zwraca 400).
5. Sukces fazy 0: jeden SVG z `vendor/axidraw/examples` narysowany bez zmian pluginu.
6. Dopiero potem KiCad rev A (Pico moduł, 3× socket, DNP AS5600+LSM6).

### Read next
- `hardware/PINOUT.md` — pełny pinout + dual osi 2
- `hardware/PROTO-SCIEGA.html` — ściąga montażu proto
- `hardware/POWER.md` — VMOT / 5 V / 3V3, ADC GP28
- `firmware/README.md` — build i wgrywanie UF2
- `firmware/include/board_pins.h` — stałe GPIO
- `docs/PLAN.md` — fazy; KiCad po teście pluginu
- `docs/PROTOCOL.md` — komendy, których plugin używa
- `tools/ebb_sim/ebb_protocol.py` — złoty model odpowiedzi EBB

### Git
- Branch: `main`
- Last commit: `e5aa85d` Lock Pico toolchain, EiBotBoard UF2 path, and proto pinout for three drivers.
- Remote: https://github.com/ZwinnySerwis/axidraw-modern

### Paste prompt
> Przeczytaj @HANDOFF.md — tylko najnowszy wpis (ostatni, z datą) jest aktualny; starsze to historia. Potem otwórz pliki z sekcji Read next i krótko potwierdź, że rozumiesz stan. Nie powtarzaj zamkniętych decyzji. Zaczynamy od: wgranie firmware/build/axidraw_modern.uf2 na Pico (BOOTSEL → RPI-RP2), sprawdzenie że stockowy plugin widzi EiBotBoard, potem STEP/DIR na DRV8825 według hardware/PINOUT.md. KiCad dopiero po tym teście.
