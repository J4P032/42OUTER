---
name: Render and Clear Screen
description: Refrescar/limpiar la pantalla de consola en C++ usando la función clearScreen() con escapes ANSI nativos (evita el parpadeo en animaciones y no usar system("clear"/"cls")).
---

# Skill: Render and Clear Screen

## Description
Usa secuencias de escape ANSI nativas para limpiar la terminal y posicionar el cursor al inicio (0,0) antes de dibujar el tablero. Esto evita el parpadeo en las animaciones de consola en C++.

## Usage Guide
Cuando necesites refrescar la pantalla en C++, genera esta función exacta en el código:

```cpp
void clearScreen() {
    // Limpia la pantalla y mueve el cursor arriba a la izquierda
    std::cout << "\033[2J\033[1;1H";
}
```
No uses `system("clear")` ni `system("cls")` porque rompen la portabilidad.
