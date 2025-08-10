# VTFEdit-Reloaded Dependencies Checker
# Este script verifica que todas las dependencias del proyecto esten presentes

Write-Host "=== VTFEdit-Reloaded Dependencies Checker ===" -ForegroundColor Green
Write-Host "Verificando dependencias del proyecto..." -ForegroundColor Yellow

# Verificar dependencias del proyecto
$dependencies = @{
    "HLLib.dll" = "thirdparty\bin\HLLib.dll"
    "DevIL.dll" = "thirdparty\bin\DevIL.dll"
    "Compressonator_MT.lib" = "thirdparty\lib\Compressonator_MT.lib"
    "Compressonator_MTd.lib" = "thirdparty\lib\Compressonator_MTd.lib"
    "DevIL.lib" = "thirdparty\lib\DevIL.lib"
    "Compressonator.h" = "thirdparty\include\Compressonator.h"
    "stb_image_resize.h" = "thirdparty\include\stb_image_resize.h"
    "IL headers" = "thirdparty\include\IL"
}

$allDependenciesPresent = $true
$missingDependencies = @()

foreach ($dep in $dependencies.GetEnumerator()) {
    if (Test-Path $dep.Value) {
        Write-Host "OK $($dep.Key) - Presente" -ForegroundColor Green
    } else {
        Write-Host "ERROR $($dep.Key) - Faltante" -ForegroundColor Red
        $allDependenciesPresent = $false
        $missingDependencies += $dep.Key
    }
}

Write-Host "`n=== RESUMEN ===" -ForegroundColor Cyan

if ($allDependenciesPresent) {
    Write-Host "OK Todas las dependencias del proyecto estan presentes!" -ForegroundColor Green
    Write-Host "`nEl proyecto esta listo para compilar." -ForegroundColor Green
} else {
    Write-Host "ERROR Faltan las siguientes dependencias:" -ForegroundColor Red
    foreach ($missing in $missingDependencies) {
        Write-Host "   - $missing" -ForegroundColor Red
    }
    Write-Host "`nPor favor, descarga las dependencias faltantes antes de compilar." -ForegroundColor Yellow
}

# Verificar si Visual Studio Build Tools esta instalado
Write-Host "`n=== VERIFICACION DEL COMPILADOR ===" -ForegroundColor Cyan

$vsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer"
if (Test-Path $vsPath) {
    Write-Host "OK Visual Studio Installer encontrado" -ForegroundColor Green
    
    # Buscar instalaciones de Visual Studio
    $vsInstallations = Get-ChildItem $vsPath -Name "*.exe" | Where-Object { $_ -like "*vswhere*" }
    if ($vsInstallations) {
        $vswherePath = Join-Path $vsPath $vsInstallations[0]
        try {
            $installPath = & $vswherePath -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
            if ($installPath) {
                Write-Host "OK Visual Studio Build Tools encontrado en: $installPath" -ForegroundColor Green
                
                # Verificar si msbuild esta disponible
                $msbuildPath = Join-Path $installPath "MSBuild\Current\Bin\MSBuild.exe"
                if (Test-Path $msbuildPath) {
                    Write-Host "OK MSBuild encontrado" -ForegroundColor Green
                } else {
                    Write-Host "ERROR MSBuild no encontrado" -ForegroundColor Red
                }
            } else {
                Write-Host "ERROR Visual Studio Build Tools no encontrado" -ForegroundColor Red
                Write-Host "   Instala 'Desktop development with C++' workload" -ForegroundColor Yellow
            }
        } catch {
            Write-Host "ERROR Error al verificar Visual Studio Build Tools" -ForegroundColor Red
        }
    }
} else {
    Write-Host "ERROR Visual Studio Installer no encontrado" -ForegroundColor Red
    Write-Host "   Instala Visual Studio Build Tools primero" -ForegroundColor Yellow
}

Write-Host "`nPresiona Enter para salir..." -ForegroundColor Gray
Read-Host 