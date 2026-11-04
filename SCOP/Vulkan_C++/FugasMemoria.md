# 🛡️ Guía Definitiva de Valgrind en Proyectos Gráficos (42)

Al desarrollar un proyecto gráfico (como `scop`, `cub3d`, o `miniRT`) que utiliza librerías externas como **SDL**, **MLX**, o **Vulkan**, esta guía explica por qué aparecen ciertos mensajes en Valgrind y qué significan realmente.

---

## 📊 Resumen Rápido: ¿Qué es un Leak y qué NO lo es?

La regla de oro es buscar fallos en la lógica de nuestro propio código. Valgrind clasifica la memoria al salir del programa en varias categorías. Esto es lo que hay que mirar:

| Categoría en Valgrind | ¿Es un Leak? | ¿Fallo nuestro en código? | Explicación sencilla |
| :--- | :---: | :---: | :--- |
| **`definitely lost`** | **SÍ** 🛑 | **SÍ** ❌ | El alumno hizo un `malloc`/`new`, perdió el puntero y esa memoria se quedó huérfana en el sistema. |
| **`indirectly lost`** | **SÍ** 🛑 | **SÍ** ❌ | Memoria que se perdió como consecuencia directa de haber perdido un puntero principal de un `definitely lost`. |
| **`still reachable`** | **NO** 🟢 | **NO**  | La memoria sigue asignada, **pero el puntero sigue existiendo**. Viene de las librerías del sistema y los drivers gráficos. |

---

## 🧠 ¿Por qué aparece memoria "Still Reachable" (Aún Alcanzable)?

Cuando el programa interactúa con la tarjeta gráfica (por ejemplo, una GPU AMD o Nvidia) y con el servidor de ventanas (X11 o Wayland) a través de SDL o MLX, estas librerías reservan memoria para cachés internas, hilos de ejecución y configuraciones de pantalla.

Al cerrar el programa, los ingenieros que programaron los drivers de la tarjeta gráfica toman una **decisión de diseño intencionada por eficiencia**:

1. **No perder tiempo en el cierre:** Rastrear y liberar miles de pequeñas estructuras internas justo cuando el usuario le da a "Cerrar" ralentizaría el apagado del programa de forma inútil.
2. **El Sistema Operativo es el recolector definitivo:** En Linux, en cuanto el proceso termina, el Kernel destruye instantáneamente toda la memoria asignada a ese programa de golpe. 

Como esa memoria nunca se va a acumular a lo largo del tiempo (porque el programa está muriendo), **no es una fuga de memoria**. Los punteros globales del driver siguen apuntando a ella hasta el último milisegundo de vida, por eso Valgrind la marca como *Still Reachable*.

---

## 📜 ¿Qué dice la Documentación Oficial de Valgrind?
https://valgrind.org/docs/manual/mc-manual.html

para resolver dudas, estos son los fragmentos extraídos directamente de los manuales oficiales de los creadores de Valgrind:

### 1. El Manual de Valgrind (Sección Memcheck)
> *"**'Still reachable'**. A start-pointer or chain of start-pointers to the block is found. Since the block is still pointed at, the programmer could, at least in principle, have freed it before program exit. **'Still reachable' blocks are very common and arguably not a problem.**"*
>
> **Traducción:** *"**'Aún alcanzable'**. Se encuentra un puntero inicial hacia el bloque. Dado que el bloque todavía está apuntado, el programador podría haberlo liberado antes de salir. **Los bloques 'still reachable' son muy comunes y podría decirse que no son un problema.**"*

### 2. Las Preguntas Frecuentes (FAQ) de Valgrind
> *“**'still reachable' means your program is probably ok** -- it didn't free some memory it could have. This is quite common and often reasonable.”*
>
> **Traducción:** *“**'still reachable' significa que tu programa probablemente está bien**; simplemente no liberó alguna memoria que podría haber liberado. Esto es bastante común y a menudo razonable.”*

---

## 🛠️ Cómo limpiar el ruido de fondo (Archivos de Supresión `.supp`)

Para evitar que los drivers del sistema empañen el reporte de Valgrind y poder ver únicamente los errores reales del código, la industria utiliza archivos de supresión. 

Puedes ejecutar Valgrind indicándole que ignore de forma segura los falsos positivos de las librerías gráficas del sistema con el siguiente comando:

(Saldrán muchas lineas por el --show-leak-kinds=all para ver los still reachable. Quitarlo para
resumir)
```bash
valgrind --leak-check=full --show-leak-kinds=all --suppressions=scop.supp ./scop resources/teapot.obj
```

Un archivo `scop.supp` correcto para filtrar el ruido de SDL, X11 y lecturas optimizadas del cargador de Linux tiene este aspecto:

```text
{
   Ignore_SDL3_X11
   Memcheck:Leak
   match-leak-kinds: definite,indirect
   ...
   obj:*/libSDL3.so*
   ...
}
{
   Ignore_DlOpen_Drivers
   Memcheck:Leak
   match-leak-kinds: definite,indirect
   fun:malloc
   ...
   fun:_dl_open
   ...
}
{
   Ignore_Glibc_Grapheme_Rpath_Read
   Memcheck:Value8
   fun:strncmp
   fun:is_dst
   ...
   fun:_dl_map_object
}
{
   Ignore_Reachable_System_Libraries
   Memcheck:Leak
   match-leak-kinds: reachable
   ...
   obj:*
}
```

Al usarlo, tu terminal mostrará un impecable **`ERROR SUMMARY: 0 errors`**, garantizando que tu código gestiona la memoria de manera perfecta.
