# Firmware axidraw-modern (RP2040)

Cel: USB CDC mówiące protokołem EBB, impulsy STEP/DIR na dwóch stepstickach, PWM serwa.

## Stan

Szkielet C (parser + piny + pętla CDC). Logika protokołu jest najpierw domknięta w Pythonie: `tools/ebb_sim` — tam łapiemy zgodność z pluginem zanim wgramy UF2.

## Toolchain (Windows)

Zainstalowane lokalnie (2026-10-10): CMake, Ninja, ARM GCC 14.2, Pico SDK 2.1.1 w `C:\Users\Kleszcz\pico-sdk`, picotool 2.1.1 w `C:\Users\Kleszcz\pico-tools`. `PICO_SDK_PATH` jest w zmiennych użytkownika.

```powershell
cd firmware
. .\env.ps1
cmake -S . -B build -G Ninja -DPICO_BOARD=pico `
  -Dpicotool_DIR="C:/Users/Kleszcz/pico-tools/picotool" `
  -Dpioasm_DIR="C:/Users/Kleszcz/pico-tools/pioasm"
cmake --build build
```

Wychodzi `firmware/build/axidraw_modern.uf2`.

**Nie wgrywamy przez PlatformIO.** To Pico SDK + CMake + Ninja. PlatformIO na tej maszynie ma ARM GCC 7.2 — za stary.

Wgrywanie:

1. Pico: przycisk BOOTSEL, włożyć USB → dysk `RPI-RP2`.
2. Skopiować `firmware/build/axidraw_modern.uf2` na ten dysk. Pico sam resetuje.
3. Albo, gdy już jest CDC: `picotool load firmware/build/axidraw_modern.uf2 -f` (wymaga BOOTSEL albo resetu przez USB).

## USB

- `iManufacturer`: `axidraw-modern`
- `iProduct`: `EiBotBoard`  ← wymagane przez `plotink.ebb_serial.findPort`
- VID/PID: zostawiamy Raspberry Pi (`2E8A`) — nie podszywamy się pod Microchip `04D8:FD92`

## Mapowanie COM na Windows

Po wgraniu: Menedżer urządzeń → port COM. Plugin powinien zobaczyć `EiBotBoard`. Jeśli Windows nazwie urządzenie „USB Serial Device”, sprawdzamy deskryptor i ewentualnie dopisujemy nasz VID w forku `findPort` (to jedyny dopuszczalny patch hosta w MVP).
