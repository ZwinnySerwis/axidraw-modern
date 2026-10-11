# Session env for Pico SDK + ARM GCC (phase 0). Dot-source from firmware/:
#   . .\env.ps1
$env:PICO_SDK_PATH = "C:\Users\Kleszcz\pico-sdk"
$armBin = "C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\14.2 rel1\bin"
$picoTools = "C:\Users\Kleszcz\pico-tools"
foreach ($bin in @($armBin, "$picoTools\picotool", "$picoTools\pioasm")) {
    if ($env:Path -notlike "*$bin*") {
        $env:Path = "$bin;$env:Path"
    }
}
Write-Host "PICO_SDK_PATH=$env:PICO_SDK_PATH"
Write-Host "arm-none-eabi-gcc: $(arm-none-eabi-gcc --version | Select-Object -First 1)"
Write-Host "picotool: $(picotool version 2>&1 | Select-Object -First 1)"
