# Guía de Compilación - VTFEdit-Reloaded

## 🎯 Resumen

VTFEdit-Reloaded es una herramienta para editar archivos VTF (Valve Texture Format) y VMT (Valve Material Type) utilizados en juegos de Valve como Half-Life 2, Counter-Strike, etc.

## 📋 Requisitos Previos

### Software Necesario
- **Visual Studio 2019** o **Visual Studio 2022** con:
  - Carga de trabajo "Desktop development with C++"
  - Build Tools para C++
- **.NET Framework 4.8 Developer Pack** (ya instalado)

### Dependencias Incluidas
El proyecto ya incluye todas las dependencias necesarias en la carpeta `thirdparty/`:
- **Compressonator** - Para compresión DXT
- **DevIL** - Para soporte de múltiples formatos de imagen
- **HLLib** - Para soporte de archivos de Valve
- **stb_image_resize** - Para redimensionamiento de imágenes

## 🚀 Compilación Automática

### Opción 1: Script de Batch (Recomendado)
```cmd
build.bat
```

### Opción 2: Script de PowerShell
```powershell
.\build.ps1
```

### Opción 3: Compilación Manual
```cmd
"C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin\MSBuild.exe" "sln\vs2019\VTFLib.sln" /p:Configuration=Release /p:Platform=x64
```

## 📁 Estructura del Proyecto

```
VTFEdit-Reloaded/
├── sln/vs2019/           # Solución de Visual Studio
│   ├── VTFLib/          # Biblioteca principal (DLL)
│   ├── VTFEdit/         # Interfaz gráfica (EXE)
│   ├── VTFCmd/          # Línea de comandos (EXE)
│   └── Build/           # Archivos compilados (se crea)
├── thirdparty/           # Dependencias externas
│   ├── include/         # Headers
│   ├── lib/            # Bibliotecas estáticas
│   └── bin/            # DLLs
└── VTFLib/              # Código fuente de la biblioteca
```

## 🔧 Solución de Problemas

### Error: "No se encuentran los ensamblados de referencia para .NETFramework,Version=v4.0"
**Solución**: El proyecto ya está configurado para usar .NET Framework 4.8. Si persiste el error, instala el .NET Framework 4.8 Developer Pack.

### Error: "cannot open include file 'afxres.h'"
**Solución**: Ya resuelto - se reemplazó con `winres.h` en VTFCmd.

### Error: MSBuild no encontrado
**Solución**: Asegúrate de tener Visual Studio 2019 o 2022 instalado con Build Tools.

## 📦 Archivos Generados

Después de una compilación exitosa, encontrarás en `sln\vs2019\Build\`:

- **VTFEdit.exe** - Interfaz gráfica principal
- **VTFCmd.exe** - Herramienta de línea de comandos
- **VTFLib.dll** - Biblioteca principal
- **DevIL.dll** - Soporte de imágenes
- **HLLib.dll** - Soporte de archivos de Valve

## 🎮 Uso

### VTFEdit (Interfaz Gráfica)
- Ejecuta `VTFEdit.exe` para abrir la interfaz gráfica
- Permite importar/exportar texturas en múltiples formatos
- Soporta edición de archivos VMT
- Incluye herramientas de conversión por lotes

### VTFCmd (Línea de Comandos)
```cmd
VTFCmd.exe -file "textura.png" -format "dxt1" -output "output.vtf"
```

## 🔄 Recompilación

Para recompilar después de cambios:
1. Ejecuta `build.bat` o `build.ps1`
2. Los scripts limpiarán automáticamente las compilaciones anteriores
3. Se generarán nuevos ejecutables en la carpeta Build

## 📝 Notas Técnicas

- **Plataforma**: x64 (64-bit)
- **Configuración**: Release (optimizada)
- **Herramienta de compilación**: MSBuild v142 (Visual Studio 2019)
- **Soporte CLR**: Sí (para VTFEdit)
- **Dependencias**: Todas incluidas en el proyecto

## 🆘 Soporte

Si encuentras problemas:
1. Verifica que tienes Visual Studio 2019 o 2022 instalado
2. Asegúrate de tener la carga de trabajo "Desktop development with C++"
3. Ejecuta los scripts de compilación como administrador si es necesario
4. Revisa los logs de compilación para errores específicos 