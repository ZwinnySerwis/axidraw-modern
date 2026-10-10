# Wybór MCU

Oryginalna płyta: **PIC18F46J50** @ 48 MHz USB, dwa wlutowane Allegro **A4983** (v1.2+; v1.1: A3967), serwo RC, bootloader HID. Toolchain to MPLAB + C18 / MLA USB — martwy kierunek na 2026.

## Rekomendacja: Raspberry Pi Pico (RP2040), docelowo Pico 2 (RP2350)

Dla MVP bierzemy **RP2040** (Pico / Pico W). To nie jest „Arduino dla zabawek” — to najlepszy kompromis na ploter STEP/DIR.

| Kryterium | RP2040 / RP2350 | STM32G4/F4 | ESP32-S3 | zostawiamy PIC |
| --- | --- | --- | --- | --- |
| USB CDC bez kombinowania | tak (TinyUSB) | tak, więcej setupu | tak na S2/S3 | tak |
| Precyzyjne impulsy STEP | PIO, jitter ~ns | timery, robota | gorzej (Wi‑Fi ISR) | ISR 25 kHz |
| GPIO na 2× stepstick + MS + serwo | z zapasem | z zapasem | z zapasem | oryginał |
| Cena / dostępność | Pico ~4 USD | większa płyta | tania | EOL |
| Toolchain na Windows | Pico SDK + ARM GCC | STM32Cube | ESP-IDF | MPLAB C18 |
| UART do TMC2209 później | 2× UART | tak | tak | nie w praktyce |

**Dlaczego PIO:** dwa state machines generują STEP niezależnie od USB. Host może lać komendy, a krawędzie STEP nie drżą. To 1:1 z rolą ISR 25 kHz na PIC, tylko lepiej.

**RP2350 (Pico 2)** jest ulepszeniem drop-in, gdy płyta ma być „na lata” (więcej RAM, RISC-V/ARM). Firmware piszemy pod pico-sdk, więc zmiana to głównie `PICO_BOARD`.

## Czego nie bierzemy na MVP

- **ESP32** — Wi‑Fi przyda się później (plot bez PC), ale na MVP psuje determinizm i komplikuje USB. Zostawiamy jako możliwy mostek / drugi rdzeń projektu, nie jako pierwszy MCU ruchu.
- **STM32** — świetny przemysłowo, gorszy onboarding (Cube, HAL). Wrócimy, jeśli zabraknie timerów albo ADC do pomiaru VMOT.
- **SAMD21** — USB OK, za mało zapasu na FIFO + PIO-like.

## Zasoby, których MVP potrzebuje

- USB device CDC
- ≥ 8 GPIO: STEP/DIR/EN × 2
- 3 GPIO wspólne MS1/MS2/MS3 (globalny step mode jak w EBB)
- 1 PWM serwa (~50 Hz, szerokość 1–2 ms; EBB liczy w kwantach 83,3 ns)
- 1 wejście przycisku pauzy
- 1 LED
- ADC VMOT (żeby `QC` zwracało napięcie — plugin ostrzega poniżej ~250 jednostek, typowo ~300 przy 9 V)

RP2040 to pokrywa. ADC jest 12-bit; skalujemy odczyt do skali EBB, żeby plugin nie krzyczał o niskim napięciu.

## Płytka rozwojowa vs własny PCB

1. **Teraz:** Pico na płytce stykowej / proto + dwa stepsticki (np. A4988 albo TMC2209 w trybie legacy) + serwo + 12 V.
2. **Potem:** własny PCB: Pico (albo RP2040 bezpośrednio), dwa sockety 16-pin, VMOT, buck 5 V, USB-C.

Nie blokujemy MVP projektem PCB.
