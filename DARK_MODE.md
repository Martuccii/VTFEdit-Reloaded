# Modo Oscuro en VTFEdit Reloaded

## Características

- **Tema Claro**: Colores tradicionales claros (por defecto)
- **Tema Oscuro**: Colores oscuros modernos para mejor experiencia visual

## Cómo usar

1. **Cambiar tema**: Ve al menú `View` → `Theme`
2. **El tema se guarda automáticamente** en la configuración
3. **Se aplica al reiniciar** la aplicación

## Colores implementados

### Tema Claro
- Fondo: Gris claro (#F0F0F0)
- Texto: Negro (#000000)
- Controles: Blanco (#FFFFFF)

### Tema Oscuro
- Fondo: Gris muy oscuro (#202020)
- Texto: Blanco (#FFFFFF)
- Controles: Gris oscuro (#303030)

## Archivos modificados

- `VTFEdit/ThemeManager.h` - Gestor de temas
- `VTFEdit/VTFEdit.h` - Integración en la aplicación principal

## Configuración

El tema se guarda en el archivo de configuración como:
```
VTFEdit.Theme = Dark
```

## Compatibilidad

- Funciona con todas las ventanas de la aplicación
- Se aplica a controles estándar de Windows Forms
- Persiste entre sesiones 