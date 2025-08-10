@echo off
echo ========================================
echo    VTFEdit-Reloaded Build Script
echo ========================================
echo.

REM Verificar si MSBuild está disponible
set "MSBUILD_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin\MSBuild.exe"

if not exist "%MSBUILD_PATH%" (
    set "MSBUILD_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
)

if not exist "%MSBUILD_PATH%" (
    echo ERROR: No se pudo encontrar MSBuild
    echo Por favor, instala Visual Studio 2019 o 2022 con Build Tools
    pause
    exit /b 1
)

echo Usando MSBuild: %MSBUILD_PATH%
echo.

REM Limpiar compilaciones anteriores
echo Limpiando compilaciones anteriores...
if exist "sln\vs2019\Build" rmdir /s /q "sln\vs2019\Build"
if exist "sln\vs2019\VTFLib\x64\Release" rmdir /s /q "sln\vs2019\VTFLib\x64\Release"
if exist "sln\vs2019\VTFCmd\x64\Release" rmdir /s /q "sln\vs2019\VTFCmd\x64\Release"
if exist "sln\vs2019\VTFEdit\x64\Release" rmdir /s /q "sln\vs2019\VTFEdit\x64\Release"

echo.

REM Compilar el proyecto
echo Compilando VTFEdit-Reloaded...
"%MSBUILD_PATH%" "sln\vs2019\VTFLib.sln" /p:Configuration=Release /p:Platform=x64

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo    COMPILACION EXITOSA!
    echo ========================================
    echo.
    echo Archivos generados en: sln\vs2019\Build\
    echo.
    echo - VTFEdit.exe (Interfaz gráfica)
    echo - VTFCmd.exe (Línea de comandos)
    echo - VTFLib.dll (Biblioteca principal)
    echo - DevIL.dll (Soporte de imágenes)
    echo - HLLib.dll (Soporte de archivos)
    echo.
    echo Puedes ejecutar VTFEdit.exe desde la carpeta Build
    echo.
) else (
    echo.
    echo ========================================
    echo    ERROR EN LA COMPILACION
    echo ========================================
    echo.
    echo Revisa los errores anteriores
    echo.
)

pause 