# Protokół EBB — skrót pod firmware

Pełna specyfikacja: [`upstream/ebb-command-set.html`](upstream/ebb-command-set.html) oraz [ebb.html](https://evil-mad.github.io/EggBot/ebb.html).

## Link szeregowy

- USB CDC, baud w praktyce ignorowany.
- Komendy ASCII, case-insensitive, **bez spacji**, max 256 bajtów, koniec `\r`.
- Tryb legacy (domyślny, tego używa plugin):
  - komendy → linia `OK\r\n`
  - zapytania → dane + zwykle druga linia `OK`, **wyjątki** w plotink: `V`, `A`, `I`, `MR`, `PI`, `QM`, `QG` (bez dodatkowego OK).
- Błąd: `!N Err: ...` a w legacy i tak dopina `OK\r\n`.

## Detekcja

```
host → v\r
dev  → EBBv13_and_above EBB Firmware Version 2.8.1\r\n
```

USB `iProduct` musi zaczynać się od `EiBotBoard`.

## Ruch

```
SM,<Duration_ms>,<Steps1>[,<Steps2>[,<Clear>]]
XM,<Duration_ms>,<A>,<B>[,<Clear>]   →  SM(A+B, A-B)
```

Znak kroku = kierunek. Oba zera = opóźnienie (cap 100 000 ms). Max 25 000 kroków/s na oś.

`OK` wraca gdy komenda wpadnie do FIFO, nie po zakończeniu ruchu.

## Silniki i mikrokrorki

```
EM,<Enable1>[,<Enable2>]
```

Enable1: `0` wyłącz, `1` 1/16, `2` 1/8, `3` 1/4, `4` 1/2, `5` full. Enable2 nie zmienia trybu.

Plugin **nie ufa EM** przy odczycie — czyta piny PIC przez `PI`:

| Zapytanie | Znaczenie na EBB | Nasz odpowiednik |
| --- | --- | --- |
| `PI,E,0` | ENABLE1, **aktywne 0** | EN stepsticka 1 |
| `PI,C,1` | ENABLE2, aktywne 0 | EN stepsticka 2 |
| `PI,E,2` | MS1 | MS1 |
| `PI,E,1` | MS2 | MS2 |
| `PI,A,6` | MS3 | MS3 |

Mapa MS → rozdzielczość (z `ebb_motion.query_enable_motors`):

| MS1 | MS2 | MS3 | kod EM |
| --- | --- | --- | --- |
| 1 | 1 | 1 | 1 (1/16) |
| 1 | 1 | 0 | 2 (1/8) |
| 0 | 1 | 0 | 3 (1/4) |
| 1 | 0 | 0 | 4 (1/2) |
| 0 | 0 | 0 | 5 (full) |

A4988/DRV8825 mają tę samą konwencję MS. TMC w UART ustawiamy rejestrem, ale **i tak udajemy te piny w `PI`**.

## Pióro

```
SP,0[,delay[,pin]]   serwo → Servo_Max (dół)
SP,1[,delay[,pin]]   serwo → Servo_Min (góra)
SC,4,<min>           góra, jednostki 83,3 ns; default 12000 ≈ 1,00 ms
SC,5,<max>           dół; default 16000 ≈ 1,33 ms
SC,11 / SC,12        prędkość góra / dół
QP                   1 = góra, 0 = dół
```

## Zasilanie (`QC`)

`QC` zwraca `current,voltage`. Plugin alarmuje gdy voltage < 250. Typowo ~300 przy 9 V na oryginale. Skalujemy ADC VMOT tak, żeby 12 V dawało bezpiecznie > 250.
