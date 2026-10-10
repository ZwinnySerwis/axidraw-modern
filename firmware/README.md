# Firmware axidraw-modern (RP2040)

Cel: USB CDC mówiące protokołem EBB, impulsy STEP/DIR na dwóch stepstickach, PWM serwa.

## Stan

Szkielet C (parser + piny + pętla CDC). Logika protokołu jest najpierw domknięta w Pythonie: `tools/ebb_sim` — tam łapiemy zgodność z pluginem zanim wgramy UF2.

## Toolchain (Windows)

Na tej maszynie jest CMake, **brak** `arm-none-eabi-gcc` i PlatformIO.

```powershell
winget install Arm.GnuArmEmbeddedToolchain
# albo: https://github.com/raspberrypi/pico-setup-windows
```

Potem Pico SDK:

```powershell
git clone https://github.com/raspberrypi/pico-sdk.git C:\Users\Kleszcz\pico-sdk
cd C:\Users\Kleszcz\pico-sdk
git submodule update --init
$env:PICO_SDK_PATH = "C:\Users\Kleszcz\pico-sdk"
```

Build (gdy SDK i ARM GCC są na PATH):

```powershell
cd firmware
mkdir build
cd build
cmake -G Ninja -DPICO_BOARD=pico ..
ninja
```

Wychodzi `axidraw_modern.uf2`. Pico w BOOTSEL, wgrać UF2.

## USB

- `iManufacturer`: `axidraw-modern`
- `iProduct`: `EiBotBoard`  ← wymagane przez `plotink.ebb_serial.findPort`
- VID/PID: zostawiamy Raspberry Pi (`2E8A`) — nie podszywamy się pod Microchip `04D8:FD92`

## Mapowanie COM na Windows

Po wgraniu: Menedżer urządzeń → port COM. Plugin powinien zobaczyć `EiBotBoard`. Jeśli Windows nazwie urządzenie „USB Serial Device”, sprawdzamy deskryptor i ewentualnie dopisujemy nasz VID w forku `findPort` (to jedyny dopuszczalny patch hosta w MVP).
