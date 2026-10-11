# Zasilanie

Trzy domeny, wspólna masa:

| Szyna | Napięcie | Co zasila |
| --- | --- | --- |
| VMOT | 12 V (typ) albo 16–24 V | cewki silników przez stepsticki |
| 5 V | 5 V | serwo pióra; ewentualnie Pico VSYS |
| 3V3 | z Pico | logika STEP/DIR/EN/MS |

USB może zasilać sam Pico przy debugowaniu **bez** silników. Plot z silnikami: zawsze VMOT z zasilacza.

## Dzielnik ADC (`QC`)

Plugin: `voltage < 250` → ostrzeżenie. Na EBB ~300 ≈ 9 V.

Dzielnik na **GP28** (ADC2) tak, żeby 12 V VMOT dawało odczyt firmware w skali EBB około 400. Szczegóły skalowania w `firmware` — na razie emulator zwraca `0,400`. GP26/27 są I2C1 (AS5600 motor2).

## Serwo

Większość serw pióra AxiDraw to 5 V. Nie bierz 5 V z pinu Pico VBUS przy obciążeniu. Mały buck 12→5 V albo wejście 5 V zasilacza.
