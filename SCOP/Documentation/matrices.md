# Apuntes Matrices - Proyecto Scop (Vulkan)

## 1. Dimensiones y Pipeline MVP
* Matrices de transformación (Modelo, Vista, Proyección): **4x4**.
* Vértice (coordenadas homogéneas): vector columna **4x1** `[x, y, z, 1]`.
* Fórmula completa: `Punto_pantalla = Proyección × Vista × Modelo × Punto_3D`
* Paso a pantalla 2D:
  1. División perspectiva: `x' / w'` e `y' / w'`.
  2. Mapeo a ventana: escalar de `[-1, 1]` a píxeles. *(En Vulkan, Y apunta hacia abajo y Z va de `0` a `1`)*.

## 2. Cambio de Base y Traslación
* **Cambio de base:** Traducir coordenadas de un sistema de referencia a otro. El punto no se mueve, cambian los ejes.
* **Coordenadas homogéneas (`1` extra):** Necesarias para poder sumar traslaciones multiplicando matrices.
* **Regla de signos:** Al mover el origen del sistema (cambio de base), se aplica el signo opuesto:
  * Nuevo origen en `(+2, +2)` -> pones `-2, -2` en la última columna.

## 3. Matriz Identidad y Zonas de una 4x4
* **Identidad:** Diagonal de `1` y resto `0`. Punto de partida neutro.
* **Zonas de la matriz 4x4:**
  * **Última columna (`Tx, Ty, Tz`):** Traslación.
  * **Diagonal principal (bloque 3x3):** Escala (`Sx, Sy, Sz`).
  * **Bloque 3x3 completo:** Rotación (y combinación de rotación + escala).

## 4. Matrices Modelo y Vista
* **Modelo:** `Traslación × Rotación × Escala` (4x4).
* **Vista (Cámara):** Mueve todo el mundo al revés para dejar la cámara en `(0,0,0)`:
  * `Vista = Rotación_inversa × Traslación_inversa` (sin escala).
* Total: **5 multiplicaciones de matrices** en CPU -> 1 matriz `MVP` (4x4) -> **1 multiplicación por vértice** en GPU.

## 5. Rotación en 2D y 3D
* **Interpretación:** Cada columna de la matriz guarda hacia dónde apunta el nuevo eje (Col 0 = X, Col 1 = Y, Col 2 = Z).
* **Signo del ángulo:** Si giras los ejes `+45°` (cambio de base), usas `-45°` en la fórmula.
* **Plantilla 2D:**
  `[ cos(θ)  -sin(θ) ]`
  `[ sin(θ)   cos(θ) ]`

* **Plantillas 3D (añadir fila/columna identidad para 4x4):**
  * **Eje Z:**
    `[ cos(θ)  -sin(θ)  0 ]`
    `[ sin(θ)   cos(θ)  0 ]`
    `[   0        0     1 ]`
  * **Eje X:**
    `[ 1    0        0    ]`
    `[ 0  cos(θ)  -sin(θ) ]`
    `[ 0  sin(θ)   cos(θ) ]`
  * **Eje Y:**
    `[  cos(θ)  0  sin(θ) ]`
    `[    0     1    0    ]`
    `[ -sin(θ)  0  cos(θ) ]`
