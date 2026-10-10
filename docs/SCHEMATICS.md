# Schematy OEM (PIC18F46J50)

AxiDraw używa **EiBotBoard (EBB) v2.7** — to jest ta sama płyta co EggBot/WaterColorBot. CPU: **PIC18F46J50-I/PT**, dwa **Allegro A4983** wlutowane. Pliki są CC-BY (Brian Schmalz / Schmalz Haus), nie w repo AxiDraw.

## Najważniejsze (to bierzemy do KiCada jako referencję)

Lokalnie, już w repo:

| Plik | Co to jest |
| --- | --- |
| `docs/upstream/oem/EBB_v27/EBB_v27/EiBotBoard-v27.sch` | Eagle schematic — **źródło** |
| `docs/upstream/oem/EBB_v27/EBB_v27/EiBotBoard-v27.brd` | Eagle PCB |
| `docs/upstream/oem/EBB_v27/EBB_v27/EiBotBoard-v27_sch.pdf` | ten sam schemat jako PDF |
| `docs/upstream/oem/EBB_v27/EBB_v27/EiBotBoard-v27_brd.pdf` | layout PDF |
| `docs/upstream/oem/EBB_v27/EBB_v27/EiBotBoard_v27_BOM.xlsx` | BOM |
| `docs/upstream/EiBotBoard-v27_sch.pdf` | kopia PDF (pobrana wcześniej) |

Źródło sieciowe:

- Indeks: https://www.schmalzhaus.com/EBB/
- ZIP v2.7 (Eagle + gerbery + BOM): https://www.schmalzhaus.com/EBB/EBB/EBB_v27/EBB_v27.zip
- PDF schematu: https://www.schmalzhaus.com/EBB/EBB/EBB_v27/EiBotBoard-v27_sch.pdf

Starsze rewizje z tym samym PIC18F46J50: `EBB_v26`, `EBB_v25`, … na tej samej stronie. v1.1 bywała na PIC18F45J50 **albo** 46J50 i miała A3967 zamiast A4983 — nie używać jako wzoru prądowego.

SparkFun v2.4 (Eagle, nie najnowsze): https://github.com/sparkfun/EiBotBoard

Firmware PIC (nie schemat): `vendor/EggBot/EBB_firmware/`

## Co z OEM bierzemy, a czego nie kopiujemy

Bierzemy: USB CDC jako model protokołu, serwo pióra, przycisk pauzy, pomiar VMOT, polarność EN (aktywne LOW), globalne MS1–3, kolejka `SM`/`XM`.

Nie kopiujemy 1:1: PIC, A4983, trimpot prądu, HID bootloader, VID Microchip `04D8:FD92`. Zamiast sterowników — gniazda stepstick.
