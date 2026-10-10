# Pinout MVP — Raspberry Pi Pico ↔ 2× stepstick + serwo

Numeracja GPIO Pico (nie numery nóżek płytki). Wspólne MS1–3 jak globalny step mode EBB.

```
                    Pico
              ┌──────────────┐
     USB CDC  │ USB          │
              │              │
      GP2  ───│ STEP1        │── stepstick 1 (motor1 / EBB axis 1)
      GP3  ───│ DIR1         │
      GP4  ───│ EN1  (LOW=on)│  A4988/DRV8825/TMC: EN aktywne 0
              │              │
      GP5  ───│ STEP2        │── stepstick 2 (motor2 / EBB axis 2)
      GP6  ───│ DIR2         │
      GP7  ───│ EN2  (LOW=on)│
              │              │
      GP10 ───│ MS1          │── oba sticki (zworki albo równolegle)
      GP11 ───│ MS2          │
      GP12 ───│ MS3          │
              │              │
      GP15 ───│ SERVO PWM    │── serwo pióra (sygnał; 5 V i GND z bucka)
      GP14 ───│ PAUSE        │── przycisk do GND, pull-up (QB)
      GP26 ───│ ADC VMOT     │── dzielnik napięcia VMOT (QC)
      GP25 ───│ LED          │── onboard Pico
              └──────────────┘
```

SLEEP/RESET na stepstickach: do 3V3 (albo razem z EN, jeśli moduł tak ma).

## Polarność

- EN A4988/DRV8825/TMC: **LOW = silnik zasilony** — tak samo jak A4983 na EBB.
- DIR: 0/1 mapujemy 1:1 na znak kroków w `SM`. Jeśli rama jedzie w złą stronę, odwracamy w firmware jedną stałą, nie w pluginie.
- STEP: narastające zbocze (A4988).

## TMC2209 później

Na MVP: jumpers UART-off, STEP/DIR jak A4988. Potem: UART na GP8/GP9, prąd i stealthChop z komend własnych albo z `CU`. `PI` i tak udaje MS1–3.

## Nie podłączamy

Pico **nie** zasila VMOT. 12–24 V tylko na sticki. GND wspólna: zasilacz silników ↔ Pico.
