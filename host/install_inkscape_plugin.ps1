$ErrorActionPreference = "Stop"
$root = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$src = Join-Path $root "vendor\axidraw\inkscape driver"
$dst = Join-Path $env:APPDATA "inkscape\extensions"

if (-not (Test-Path $src)) {
    throw "Missing upstream plugin at $src — init git submodules first."
}

New-Item -ItemType Directory -Force -Path $dst | Out-Null
Copy-Item -Path (Join-Path $src "*") -Destination $dst -Recurse -Force
Write-Host "Copied AxiDraw Inkscape driver -> $dst"
Write-Host "Restart Inkscape. Menu: Extensions -> AxiDraw"
