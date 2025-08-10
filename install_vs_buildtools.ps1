# Script para instalar Visual Studio Build Tools
# Este script instala las herramientas necesarias para compilar VTFEdit

Write-Host "=== Instalador de Visual Studio Build Tools ===" -ForegroundColor Green
Write-Host "Este script instalara Visual Studio Build Tools para compilar VTFEdit" -ForegroundColor Yellow

# Verificar si Chocolatey esta instalado
Write-Host "`n1. Verificando Chocolatey..." -ForegroundColor Cyan
if (Get-Command choco -ErrorAction SilentlyContinue) {
    Write-Host "OK Chocolatey ya esta instalado." -ForegroundColor Green
} else {
    Write-Host "Instalando Chocolatey..." -ForegroundColor Yellow
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    Write-Host "Chocolatey instalado correctamente." -ForegroundColor Green
}

# Instalar Visual Studio Build Tools
Write-Host "`n2. Instalando Visual Studio Build Tools..." -ForegroundColor Cyan
Write-Host "Esto puede tomar varios minutos..." -ForegroundColor Yellow
choco install visualstudio2022buildtools --package-parameters "--add Microsoft.VisualStudio.Workload.VCTools --includeRecommended" -y

# Instalar Windows SDK
Write-Host "`n3. Instalando Windows SDK..." -ForegroundColor Cyan
choco install windows-sdk-10-version-2004-all -y

Write-Host "`n=== INSTALACION COMPLETADA ===" -ForegroundColor Green
Write-Host "`nAhora puedes compilar VTFEdit usando:" -ForegroundColor Yellow
Write-Host "1. El script: .\build.bat" -ForegroundColor White
Write-Host "2. O Visual Studio: sln\vs2019\VTFLib.sln" -ForegroundColor White

Write-Host "`nPresiona Enter para salir..." -ForegroundColor Gray
Read-Host 