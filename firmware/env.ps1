# Session env for Pico SDK + ARM GCC. Dot-source from firmware/:
#   . .\env.ps1
$env:PICO_SDK_PATH = "C:\Users\ZS\pico-sdk"
$armBin = "C:\Users\ZS\arm-gnu-toolchain\bin"
if ($env:Path -notlike "*$armBin*") {
    $env:Path = "$armBin;$env:Path"
}
Write-Host "PICO_SDK_PATH=$env:PICO_SDK_PATH"
Write-Host "arm-none-eabi-gcc: $(arm-none-eabi-gcc --version | Select-Object -First 1)"
