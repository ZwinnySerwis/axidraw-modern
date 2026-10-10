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
- Last commit: (uzupełnij po pushu tego handoffu)
- Remote: https://github.com/ZwinnySerwis/axidraw-modern

### Paste prompt
> Przeczytaj @HANDOFF.md — tylko najnowszy wpis (ostatni, z datą) jest aktualny; starsze to historia. Potem otwórz pliki z sekcji Read next i krótko potwierdź, że rozumiesz stan. Nie powtarzaj zamkniętych decyzji. Zaczynamy od: faza 0 z docs/PLAN.md — toolchain Pico SDK/ARM GCC, USB CDC jako EiBotBoard na Pico 264 kB, potem STEP/DIR na proto według hardware/PINOUT.md. PCB KiCad dopiero po tym, jak plugin zobaczy urządzenie.
