# Architektura MVP

```
Inkscape  →  axidraw.py / plotink  →  USB CDC  →  firmware  →  stepstick × 2 + serwo
   SVG          planowanie ruchu         EBB ASCII      STEP/DIR/EN        silniki
```

## Co zostaje z oryginału

Oryginalna AxiDraw to trzy warstwy:

1. **Plugin / CLI (Python)** — otwiera SVG, tnie ścieżki, planuje prędkość, zamienia XY na kroki, wysyła komendy EBB.
2. **plotink** — wykrywa port (`EiBotBoard` albo `VID:PID=04D8:FD92`), wysyła ASCII + `\r`, czyta `OK`.
3. **EiBotBoard** — PIC18F46J50 + dwa Allegro A4983 (nowsze rewizje; v1.1 miało A3967), serwo pióra na RB1.

Warstwy 1–2 są wystarczająco dobre na MVP. Warstwa 3 jest tym, co wymieniamy.

## Co wymieniamy

Nowa płyta:

- MCU z natywnym USB (RP2040 / RP2350 — uzasadnienie w [`MCU.md`](MCU.md)).
- Dwa gniazda stepstick (A4988 / DRV8825 / TMC2208/2209 w trybie STEP/DIR).
- PWM serwa pióra.
- Przycisk pauzy (odpowiednik PRG).
- VMOT 12–24 V osobno od 5 V logiki.

Oryginalny EBB miał już tryb `SC,2,1`: MCU steruje zewnętrznymi sterownikami STEP/DIR. My robimy to natywnie, bez wlutowanych A4983.

## Kompatybilność z pluginem (bez zmian UI)

`plotink.ebb_serial.findPort()`:

1. Opis portu zaczyna się od `EiBotBoard`.
2. Albo `USB VID:PID=04D8:FD92` (Microchip — **nie kopiujemy** tego VID/PID).

`testPort()` wysyła `v\r` i wymaga odpowiedzi zaczynającej się od `EBB`.

Wniosek: ustawiamy USB `iProduct = "EiBotBoard"` i odpowiadamy:

```
EBBv13_and_above EBB Firmware Version 2.8.1
```

Wersja `2.8.1` przechodzi wszystkie `min_fw_version` obecnego pluginu (m.in. 2.2.3 QC, 2.5.5 nicknames, 2.6.2 HM/QS).

## Kinematyka

AxiDraw (i CoreXY / H-bot) używa `XM`:

```
motor1 = A + B
motor2 = A - B
```

Host już to liczy. Firmware wykonuje dwa liczniki kroków w czasie `Duration` ms, jak `SM`.

`doXYMove` w plotink wysyła `SM,duration,delta_y,delta_x` — oś 1 = Y, oś 2 = X na EggBocie; na AxiDraw i tak idzie przez warstwę mieszanych osi. Pinout silników musi zgadzać się z kolejnością motor1/motor2 w firmware, nie z etykietami X/Y na ramie.

## Kolejka ruchu

Oryginał ma FIFO. Plugin „drip-feeduje” `SM`/`XM`/`SP` i spodziewa się `OK` gdy komenda **została przyjęta do kolejki**, nie gdy ruch się skończył. Zapytania (`QG`, `QB`) są natychmiastowe.

MVP: FIFO o głębokości ≥ 8 (EBB bywa konfigurowane `CU,4,n`). Bez FIFO plugin będzie się jąkał albo timeoutować.

ISR / PIO: oryginał kwantuje kroki do 25 kHz (40 µs). PIO na RP2040 może być dokładniejsze; dla zgodności trzymamy limit 25 000 kroków/s.

## Komendy MVP

Plugin + plotink naprawdę wołają:

| Komenda | Po co |
| --- | --- |
| `V` | Wykrycie EBB + wersja FW |
| `EM` | Enable + mikrokrorki (MS1–3) |
| `SM` / `XM` | Ruch / pauza czasowa |
| `SP` / `TP` | Pióro góra/dół |
| `SC` | Pozycje i prędkości serwa |
| `QP` `QB` `QS` `QG` `QC` | Stan |
| `PI` | Enable i MS pinów (tak plugin czyta rozdzielczość!) |
| `PO` `PD` | GPIO (laser / warstwy) |
| `SL` `QL` | Zmienna 8-bit |
| `SR` | Timeout zasilania serwa |
| `CS` | Zerowanie pozycji kroków |
| `ES` | Stop + flush FIFO |
| `HM` | Home / ruch absolutny (FW ≥ 2.6.2) |
| `ST` `QT` `RB` | Nick, reboot (opcjonalne w MVP) |

`LM` (ruch z przyspieszeniem) jest w plotink, ale podstawowy plot AxiDraw idzie przez `SM`/`XM`. MVP może zwrócić błąd na `LM` i dodać go w kolejnej iteracji, jeśli test plotu go nie woła.

## Świadoma decyzja: nie forujemy pluginu teraz

Fork UI/Inkscape pojawi się dopiero gdy:

- USB product string nie wystarczy na Windows (wtedy dopisujemy nasz VID w `findPort`), albo
- chcemy własne opcje (prąd TMC, Wi‑Fi, trzecia oś).

Do tego czasu instalujemy oryginalny plugin z `vendor/axidraw`.
