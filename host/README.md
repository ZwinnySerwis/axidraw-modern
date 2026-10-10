# Host (Inkscape) — MVP bez forka pluginu

Na MVP **nie ruszamy UI**. Instalujemy oryginalne rozszerzenie z `vendor/axidraw`. Firmware ma udawać EBB, więc menu *Extensions → AxiDraw* ma działać jak na fabrycznej maszynie.

## Instalacja na Windows

1. Zainstaluj [Inkscape 1.3+](https://inkscape.org/) (na tej maszynie jeszcze go nie było).
2. Uruchom:

```powershell
cd C:\Users\Kleszcz\Projects\axidraw-modern
.\host\install_inkscape_plugin.ps1
```

Skrypt kopiuje `vendor/axidraw/inkscape driver/*` do `%APPDATA%\inkscape\extensions\`.

Zależności Pythona Inkscape (pyserial, plotink, lxml, …) zwykle instaluje oficjalny installer AxiDraw. Przy ręcznej kopii:

```powershell
& "$env:APPDATA\..\Local\Programs\Python\Python313\python.exe" -m pip install pyserial packaging lxml plotink
```

Albo użyj instalatora z wiki: https://wiki.evilmadscientist.com/Axidraw_Software_Installation

## Kiedy wolno ruszyć plugin

Tylko jeśli Windows nie pokaże urządzenia jako `EiBotBoard` (zostanie „USB Serial Device”). Wtedy jedna zmiana w kopii `plotink/ebb_serial.py`: w `findPort` dodać nasz VID Raspberry Pi `2E8A` albo dokładny COM. To jest cały dopuszczalny diff hosta w MVP.

CLI (`vendor/axidraw/cli`) zostaje na później — ten sam protokół, inny launcher.
