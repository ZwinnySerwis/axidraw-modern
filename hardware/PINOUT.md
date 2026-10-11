# Pinout — Raspberry Pi Pico

Ściąga do druku (A4 poziomo): [`PROTO-SCIEGA.html`](PROTO-SCIEGA.html) — otwórz w przeglądarce, Ctrl+P.

Numeracja poniżej to GPIO Pico (nie numery nóżek płytki). Wspólne MS1–3 jak globalny step mode EBB.

**AS5600** (bez L): adres I2C na stałe `0x36` — OTP programuje kąt/config, **nie** adres. Dwa chipy = dwa I2C albo mux.  
**AS5600L**: domyślnie `0x40`, adres da się zmienić (tymczasowo w RAM albo spalić OTP). To pewnie ta „metoda zmiany adresu”. Na rev A zostawiamy **dwa I2C** — działa z zwykłym AS5600 i z L; jeden bus ma sens dopiero gdy na stole są dwa L.

LSM6DS3TR-C na SPI (input shaping później: wyższy ODR, bez kolizji z odczytem enkoderów).

Trzeci stepstick **nie** idzie równolegle na cewki jednego sterownika. Osobny driver, te same STEP/DIR co oś 2 (gantry / dual-Y). Plugin EBB nadal widzi dwie osie.

```
                    Pico
              ┌──────────────┐
     USB CDC  │ USB          │
              │              │
      GP0  ───│ I2C0 SDA     │── AS5600 motor1 (oś 1)     [później]
      GP1  ───│ I2C0 SCL     │
              │              │
      GP2  ───│ STEP1        │── stepstick 1 (motor1 / EBB axis 1)
      GP3  ───│ DIR1         │
      GP4  ───│ EN1  (LOW=on)│  A4988/DRV8825/TMC: EN aktywne 0
              │              │
      GP5  ───│ STEP2        │── stepstick 2 (motor2 / EBB axis 2)
      GP6  ───│ DIR2         │── na PCB: ten sam STEP/DIR → stepstick 3
      GP7  ───│ EN2  (LOW=on)│
              │              │
      GP8  ───│ TMC UART TX  │── 3× TMC później (osobne adresy UART)
      GP9  ───│ TMC UART RX  │── MVP: jumpers UART-off
              │              │
      GP10 ───│ MS1          │── wszystkie sticki (zworki albo równolegle)
      GP11 ───│ MS2          │
      GP12 ───│ MS3          │
      GP13 ───│ EN3  (LOW=on)│── stepstick 3 (slave osi 2; prąd osobno)
              │              │
      GP14 ───│ PAUSE        │── przycisk do GND, pull-up (QB)
      GP15 ───│ SERVO PWM    │── serwo pióra (sygnał; 5 V i GND z bucka)
              │              │
      GP16 ───│ SPI0 MISO    │── LSM6DS3TR-C SDO            [później]
      GP17 ───│ SPI0 CSn     │── LSM6 CS (aktywne 0)
      GP18 ───│ SPI0 SCK     │── LSM6 SPC
      GP19 ───│ SPI0 MOSI    │── LSM6 SDA/SDI
      GP22 ───│ LSM6 INT1    │── data-ready (input shaping)
              │              │
      GP20 ───│ SPARE        │
      GP21 ───│ SPARE        │
              │              │
      GP25 ───│ LED          │── onboard Pico
      GP26 ───│ I2C1 SDA     │── AS5600 motor2 (oś 2)       [później]
      GP27 ───│ I2C1 SCL     │
      GP28 ───│ ADC VMOT     │── dzielnik napięcia VMOT (QC)
              └──────────────┘
```

SLEEP/RESET na stepstickach: do 3V3 (albo razem z EN, jeśli moduł tak ma).

Stepstick 3: STEP/DIR **na PCB** z GP5/GP6 (oś 2), EN z GP13. Opcjonalny jumper DIR3 odwrócony, gdy drugi silnik gantry ma lustrzaną cewkę. Nie łączymy A+/A−/B+/B− dwóch silników w jeden stick.

VMOT jest na **GP28** (ADC2), nie GP26: GP26/27 to jedyna wolna para I2C1, która nie gryzie się ze STEP/DIR, MS ani SPI IMU.

## Polarność

- EN A4988/DRV8825/TMC: **LOW = silnik zasilony** — tak samo jak A4983 na EBB.
- DIR: 0/1 mapujemy 1:1 na znak kroków w `SM`. Jeśli rama jedzie w złą stronę, odwracamy w firmware jedną stałą, nie w pluginie.
- STEP: narastające zbocze (A4988).

## Enkodery AS5600 / AS5600L (nie MVP)

- 3V3 z Pico, pull-upy I2C ~4,7 kΩ do 3V3 na każdej parze SDA/SCL.
- DIR chipa: do GND albo 3V3 (orientacja magnesu), bez GPIO.
- Odczyt kąta po I2C; analog OUT nie podłączamy (ADC zostawiamy na VMOT).
- Dwa bus-y (I2C0 + I2C1) zostają nawet przy AS5600L — mniej zależności od palenia OTP.

## IMU LSM6DS3TR-C (nie MVP)

- SPI0, 3V3. INT2 nie podłączamy (zapas: GP20/GP21).
- I2C IMU **nie** bierzemy na MVP-plus: ten sam adres dałoby się wsadzić obok AS5600 na I2C0 (`0x6A` vs `0x36`), ale shaping chce osobnej magistrali.

## TMC2209 później

Na MVP: jumpers UART-off, STEP/DIR jak A4988. Potem: UART na GP8/GP9, prąd i stealthChop z komend własnych albo z `CU`. `PI` i tak udaje MS1–3.

## Nie podłączamy

Pico **nie** zasila VMOT. 12–24 V tylko na sticki. GND wspólna: zasilacz silników ↔ Pico.
