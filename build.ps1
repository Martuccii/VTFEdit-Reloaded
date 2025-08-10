# VTFEdit Recharged Build Script (PowerShell)
# ========================================

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "    VTFEdit Recharged Build Script" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Verificar si MSBuild está disponible
$msbuildPath = $null

if (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin\MSBuild.exe") {
    $msbuildPath = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
}
elseif (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe") {
    $msbuildPath = "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
}

if (-not $msbuildPath) {
    Write-Host "ERROR: No se pudo encontrar MSBuild" -ForegroundColor Red
    Write-Host "Por favor, instala Visual Studio 2019 o 2022 con Build Tools" -ForegroundColor Red
    Read-Host "Presiona Enter para continuar"
    exit 1
}

Write-Host "Usando MSBuild: $msbuildPath" -ForegroundColor Green
Write-Host ""

# Limpiar compilaciones anteriores
Write-Host "Limpiando compilaciones anteriores..." -ForegroundColor Yellow
if (Test-Path "sln\vs2019\Build") { Remove-Item "sln\vs2019\Build" -Recurse -Force }
if (Test-Path "sln\vs2019\VTFLib\x64\Release") { Remove-Item "sln\vs2019\VTFLib\x64\Release" -Recurse -Force }
if (Test-Path "sln\vs2019\VTFCmd\x64\Release") { Remove-Item "sln\vs2019\VTFCmd\x64\Release" -Recurse -Force }
if (Test-Path "sln\vs2019\VTFEdit\x64\Release") { Remove-Item "sln\vs2019\VTFEdit\x64\Release" -Recurse -Force }

Write-Host ""

# Compilar el proyecto
Write-Host "Compilando VTFEdit Recharged..." -ForegroundColor Yellow
$process = Start-Process -FilePath $msbuildPath -ArgumentList "sln\vs2019\VTFLib.sln", "/p:Configuration=Release", "/p:Platform=x64" -Wait -PassThru

if ($process.ExitCode -eq 0) {
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Green
    Write-Host "    COMPILACION EXITOSA!" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "Archivos generados en: sln\vs2019\Build\" -ForegroundColor White
    Write-Host ""
    Write-Host "- VTFEdit Recharged.exe (Interfaz gráfica)" -ForegroundColor White
    Write-Host "- VTFCmd.exe (Línea de comandos)" -ForegroundColor White
    Write-Host "- VTFLib.dll (Biblioteca principal)" -ForegroundColor White
    Write-Host "- DevIL.dll (Soporte de imágenes)" -ForegroundColor White
    Write-Host "- HLLib.dll (Soporte de archivos)" -ForegroundColor White
    Write-Host ""
    Write-Host "Puedes ejecutar VTFEdit Recharged.exe desde la carpeta Build" -ForegroundColor White
    Write-Host ""
} else {
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Red
    Write-Host "    ERROR EN LA COMPILACION" -ForegroundColor Red
    Write-Host "========================================" -ForegroundColor Red
    Write-Host ""
    Write-Host "Revisa los errores anteriores" -ForegroundColor Red
    Write-Host ""
}

Read-Host "Presiona Enter para continuar" 