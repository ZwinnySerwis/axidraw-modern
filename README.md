# axidraw-modern

Współczesny kontroler plotera kompatybilny z oprogramowaniem [AxiDraw](https://github.com/evil-mad/axidraw): ten sam plugin Inkscape, ten sam protokół szeregowy EBB, nowa płyta z MCU i **gniazdami na stepsticki**.

## MVP

Host (Inkscape / CLI) zostaje jak w oryginale. Cała nowość siedzi w firmware, które udaje EiBotBoard:

1. USB CDC z nazwą produktu `EiBotBoard` (plugin szuka po nazwie, potem po VID/PID).
2. Odpowiedź na `V` zaczynająca się od `EBB` i zawierająca `Firmware Version 2.8.1`.
3. Kolejka ruchu: `SM`, `XM`, `SP`, `EM` → impulsy STEP/DIR na dwóch stepstickach + PWM serwa pióra.
4. Zapytania, których plugin naprawdę używa: `QP`, `QB`, `QS`, `QC`, `PI`, `QG`, `QL`/`SL`.

Kinematyka AxiDraw (mieszane osie / H-bot) liczy **host** i wysyła `XM` albo `SM`. Firmware nie musi znać geometrii ramienia — wykonuje dwa silniki w zadanym czasie.

## Układ repo

| Ścieżka | Co tam jest |
| --- | --- |
| `vendor/axidraw` | Upstream: plugin Inkscape, CLI, Python API |
| `vendor/EggBot` | Upstream: firmware EBB (PIC18) + HEX |
| `vendor/plotink` | Upstream: komunikacja USB/serial z EBB |
| `docs/` | Architektura, wybór MCU, protokół |
| `docs/upstream/` | Zrzuty schematów i dokumentacji EBB |
| `hardware/` | Pinout Pico ↔ stepstick, zasilanie |
| `firmware/` | Nasz firmware (RP2040 / Pico) |
| `host/` | Instalacja oryginalnego pluginu (MVP bez forka UI) |
| `tools/ebb_sim/` | Emulator protokołu EBB do testów bez sprzętu |
| `tests/` | Testy parsera |

## Szybki start (to środowisko)

```powershell
git clone --recurse-submodules https://github.com/ZwinnySerwis/axidraw-modern.git
cd axidraw-modern
python -m venv .venv
.\.venv\Scripts\Activate.ps1
pip install -r requirements-dev.txt
python -m pytest
```

Plugin Inkscape: zobacz [`host/README.md`](host/README.md). Firmware: [`firmware/README.md`](firmware/README.md). MCU: [`docs/MCU.md`](docs/MCU.md).

## Licencja

Oprogramowanie hosta AxiDraw / EggBot jest GPL-2.0. Ten repozytorium używa GPL-2.0 dla kodu pochodnego od pluginu. Nowy firmware w `firmware/` i emulator w `tools/` są na GPL-2.0, żeby nie mieszać licencji przy wspólnym drzewie.

Kod w `vendor/` należy do autorów upstream (Evil Mad Scientist / Bantam Tools / Schmalz Haus) i zostaje na ich licencjach.
