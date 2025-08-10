# Guía de Instalación de Dependencias - VTFEdit-Reloaded

Esta guía te ayudará a instalar todas las dependencias necesarias para compilar VTFEdit-Reloaded.

## 📋 Requisitos del Sistema

- **Sistema Operativo**: Windows 10/11 (64-bit)
- **Arquitectura**: x64
- **Memoria RAM**: Mínimo 4GB, recomendado 8GB
- **Espacio en disco**: Mínimo 10GB para la instalación completa

## 🚀 Instalación Rápida (Recomendado)

### Opción 1: Script Automático

1. **Ejecuta PowerShell como Administrador**
   - Presiona `Win + X` y selecciona "Windows PowerShell (Administrador)"

2. **Ejecuta el script de instalación**:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   .\install_dependencies.ps1
   ```

### Opción 2: Instalación Manual

Si prefieres instalar manualmente, sigue estos pasos:

## 🔧 Instalación Manual de Dependencias

### 1. Visual Studio Build Tools

**Descarga**: [Visual Studio Build Tools 2022](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)

**Instalación**:
1. Ejecuta el instalador descargado
2. Selecciona "Desktop development with C++"
3. Asegúrate de que estén marcados:
   - MSVC v143 - VS 2022 C++ x64/x86 compiler
   - Windows 10/11 SDK
   - CMake tools for Visual Studio
4. Haz clic en "Install"

**Tiempo estimado**: 15-30 minutos

### 2. Verificar Dependencias del Proyecto

Ejecuta el script de verificación:
```powershell
.\check_dependencies.ps1
```

Este script verificará que todas las dependencias estén presentes:
- ✅ HLLib.dll - Para manejo de archivos de Valve
- ✅ DevIL.dll - Para procesamiento de imágenes
- ✅ Compressonator - Para compresión DXT
- ✅ Headers necesarios (DevIL, Compressonator, stb_image_resize)

## 🏗️ Compilación del Proyecto

### Opción 1: Script Automático

```powershell
.\build.bat
```

### Opción 2: Visual Studio

1. Abre la solución: `sln\vs2019\VTFLib.sln`
2. Cambia la configuración a:
   - **Configuration**: Release
   - **Platform**: x64
3. Haz clic derecho en "VTFEdit" → "Set as Startup Project"
4. Presiona `Ctrl + Shift + B` para compilar

### Opción 3: Línea de Comandos

```powershell
cd sln\vs2019
msbuild VTFLib\VTFLib.vcxproj /p:Configuration=Release /p:Platform=x64
msbuild VTFEdit\VTFEdit.vcxproj /p:Configuration=Release /p:Platform=x64
msbuild VTFCmd\VTFCmd.vcxproj /p:Configuration=Release /p:Platform=x64
```

## 📁 Ubicación de los Ejecutables

Después de la compilación exitosa, los archivos se encontrarán en:
- **VTFEdit.exe**: `sln\vs2019\Build\`
- **VTFCmd.exe**: `sln\vs2019\x64\Release\`
- **VTFLib.dll**: `sln\vs2019\Build\`

## 🔍 Solución de Problemas

### Error: "MSBuild no encontrado"
- Verifica que Visual Studio Build Tools esté instalado correctamente
- Asegúrate de que la carga de trabajo "Desktop development with C++" esté instalada

### Error: "Dependencias faltantes"
- Ejecuta `.\check_dependencies.ps1` para identificar qué falta
- Descarga las dependencias faltantes desde los enlaces en el README principal

### Error de Compilación
- Verifica que estés usando la configuración "Release" y plataforma "x64"
- Asegúrate de que todas las dependencias estén en las carpetas correctas

### Error de Permisos
- Ejecuta PowerShell como Administrador
- Verifica que la política de ejecución permita scripts locales

## 📚 Recursos Adicionales

- **Documentación del Proyecto**: [README.md](README.md)
- **Repositorio Original**: [VTFLib](https://github.com/NeilJed/VTFLib)
- **Documentación de Valve**: [VTF Format](https://developer.valvesoftware.com/wiki/VTF)

## 🎯 Próximos Pasos

Una vez que tengas VTFEdit compilado y funcionando, podrás:

1. **Implementar el modo oscuro** - Modificando los recursos y estilos de la interfaz
2. **Añadir nuevas funciones** - Extendiendo la funcionalidad existente
3. **Mejorar la UI/UX** - Modernizando la interfaz de usuario
4. **Optimizar el rendimiento** - Mejorando la velocidad de procesamiento

## 🤝 Contribuciones

Si encuentras problemas durante la instalación o tienes sugerencias de mejora:

1. Crea un issue en el repositorio
2. Documenta el problema con capturas de pantalla si es posible
3. Incluye información del sistema (Windows version, errores específicos)

---

**¡Feliz desarrollo! 🎉** 