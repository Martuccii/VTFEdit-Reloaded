# VTFEdit Recharged Dependencies Installer
# Este script instala todas las dependencias necesarias para compilar VTFEdit

Write-Host "=== VTFEdit Recharged Dependencies Installer ===" -ForegroundColor Green
Write-Host "Instalando dependencias para compilar VTFEdit..." -ForegroundColor Yellow

# Verificar si estamos ejecutando como administrador
if (-NOT ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Host "ADVERTENCIA: Este script debe ejecutarse como administrador para instalar algunas dependencias." -ForegroundColor Red
    Write-Host "Por favor, ejecuta PowerShell como administrador y vuelve a ejecutar este script." -ForegroundColor Red
    Read-Host "Presiona Enter para continuar..."
    exit
}

# 1. Verificar si Chocolatey está instalado
Write-Host "`n1. Verificando Chocolatey..." -ForegroundColor Cyan
if (Get-Command choco -ErrorAction SilentlyContinue) {
    Write-Host "Chocolatey ya está instalado." -ForegroundColor Green
} else {
    Write-Host "Instalando Chocolatey..." -ForegroundColor Yellow
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    Write-Host "Chocolatey instalado correctamente." -ForegroundColor Green
}

# 2. Instalar Visual Studio Build Tools
Write-Host "`n2. Instalando Visual Studio Build Tools..." -ForegroundColor Cyan
Write-Host "Esto puede tomar varios minutos..." -ForegroundColor Yellow
choco install visualstudio2022buildtools --package-parameters "--add Microsoft.VisualStudio.Workload.VCTools --includeRecommended" -y

# 3. Instalar Windows SDK
Write-Host "`n3. Instalando Windows SDK..." -ForegroundColor Cyan
choco install windows-sdk-10-version-2004-all -y

# 4. Verificar dependencias del proyecto
Write-Host "`n4. Verificando dependencias del proyecto..." -ForegroundColor Cyan

$dependencies = @{
    "HLLib.dll" = "thirdparty\bin\HLLib.dll"
    "DevIL.dll" = "thirdparty\bin\DevIL.dll"
    "Compressonator_MT.lib" = "thirdparty\lib\Compressonator_MT.lib"
    "Compressonator_MTd.lib" = "thirdparty\lib\Compressonator_MTd.lib"
    "DevIL.lib" = "thirdparty\lib\DevIL.lib"
}

$allDependenciesPresent = $true

foreach ($dep in $dependencies.GetEnumerator()) {
    if (Test-Path $dep.Value) {
        Write-Host "✅ $($dep.Key) - Presente" -ForegroundColor Green
    } else {
        Write-Host "❌ $($dep.Key) - Faltante" -ForegroundColor Red
        $allDependenciesPresent = $false
    }
}

if ($allDependenciesPresent) {
    Write-Host "`n✅ Todas las dependencias del proyecto están presentes!" -ForegroundColor Green
} else {
    Write-Host "`n❌ Algunas dependencias del proyecto están faltantes." -ForegroundColor Red
}

# 5. Verificar compilador
Write-Host "`n5. Verificando compilador..." -ForegroundColor Cyan

# Agregar Visual Studio Build Tools al PATH
$vsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer"
if (Test-Path $vsPath) {
    $vsInstallPath = Get-ChildItem $vsPath -Name "*.exe" | Select-Object -First 1
    if ($vsInstallPath) {
        $vsInstallPath = Join-Path $vsPath $vsInstallPath
        $installPath = & $vsInstallPath --installPath
        if ($installPath) {
            $vcvarsPath = Join-Path $installPath "VC\Auxiliary\Build\vcvars64.bat"
            if (Test-Path $vcvarsPath) {
                Write-Host "✅ Visual Studio Build Tools encontrado en: $installPath" -ForegroundColor Green
            }
        }
    }
}

# 6. Crear script de compilación
Write-Host "`n6. Creando script de compilación..." -ForegroundColor Cyan

$buildScript = @"
@echo off
echo === VTFEdit Recharged Build Script ===

REM Configurar variables de entorno de Visual Studio
call "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath > temp_vs_path.txt
set /p VS_PATH=<temp_vs_path.txt
del temp_vs_path.txt

if "%VS_PATH%"=="" (
    echo ERROR: Visual Studio Build Tools no encontrado
    echo Por favor instala Visual Studio Build Tools primero
    pause
    exit /b 1
)

echo Visual Studio encontrado en: %VS_PATH%
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat"

REM Cambiar al directorio de la solución
cd /d "%~dp0sln\vs2019"

REM Compilar la solución
echo Compilando VTFLib...
msbuild VTFLib\VTFLib.vcxproj /p:Configuration=Release /p:Platform=x64

echo Compilando VTFEdit...
msbuild VTFEdit\VTFEdit.vcxproj /p:Configuration=Release /p:Platform=x64

echo Compilando VTFCmd...
msbuild VTFCmd\VTFCmd.vcxproj /p:Configuration=Release /p:Platform=x64

echo.
echo === Compilación completada ===
echo Los ejecutables se encuentran en: sln\vs2019\Build\
echo.
pause
"@

$buildScript | Out-File -FilePath "build.bat" -Encoding ASCII
Write-Host "✅ Script de compilación creado: build.bat" -ForegroundColor Green

# 7. Instrucciones finales
Write-Host "`n=== INSTALACIÓN COMPLETADA ===" -ForegroundColor Green
Write-Host "`nPara compilar VTFEdit:" -ForegroundColor Yellow
Write-Host "1. Ejecuta el script: .\build.bat" -ForegroundColor White
Write-Host "2. O abre la solución en Visual Studio: sln\vs2019\VTFLib.sln" -ForegroundColor White
Write-Host "3. Cambia la configuración a 'Release' y 'x64'" -ForegroundColor White
Write-Host "4. Compila el proyecto VTFEdit" -ForegroundColor White
Write-Host "`nEl ejecutable se generará en: sln\vs2019\Build\" -ForegroundColor Cyan

Write-Host "`nPresiona Enter para salir..." -ForegroundColor Gray
Read-Host 