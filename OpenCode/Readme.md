## proposito
Esta es una forma de trabajar con AGENTES y SKILLS.
El ejercicio es solo hacer un gameoflife para que lo haga el ordenador.

## instrucciones
Para inicializarlo hay que escribir:
```bash
mkdir game-of-life
cd game-of-life
echo "//inicio de game of life en c++" > main.cpp
/init si queremos que nos haga la IA el MD.
```

## AGENTS.md
Es el markdown que se encarga de comunicarse con los agentes. En el le damos las normas que va a seguir el proceso de creación.

## SKILL.md
Se ha de crear en un directorio oculto dentro del proyecto:

```bash
mkdir -p .opencode/skills/render-utils
nano .opencode/skills/render-utils/SKILL.md
```
*MUY IMPORTANTE: Al principio hay que crear un bloque YAML Frontmatter que es lo que va entre "---"
en el que se mete el "name" y el "description" para que lo lea automáticamente la IA.

**NOTA: si fuera Claude sería lo mismo, pero metíendolo en .claude en vez de .opencode

## COMO SE CONSTRUYÓ con la IA:

```opencode Prompt1
Lee AGENTS.md. Modifica main.cpp para inicializar un tablero (vector bidimensional de bool) de 20 filas por 40 columnas. Haz una función para rellenarlo con valores aleatorios (true/false) y otra función que dibuje el tablero en la consola imprimiendo '#' para celdas vivas y '.' para muertas. Solo crea la estructura de inicialización y dibujo en el main.
```

```opencode Prompt2
Usa el código actual de main.cpp. Añade una función llamada countNeighbors(const std::vector<std::vector<bool>>& board, int r, int c) que devuelva cuántos de los 8 vecinos alrededor de la posición (r, c) están vivos (true). Asegúrate de controlar los límites de la rejilla para que no se salga del vector (filas entre 0 y 19, columnas entre 0 y 39). Compila para verificar que no hay errores.
```

```opencode Prompt3
Usa el código actual de main.cpp. Añade una función updateBoard que aplique las reglas del Juego de la Vida usando countNeighbors para generar el tablero del siguiente turno. Después, en la función main, crea un bucle infinito que: 1. Dibuje el tablero. 2. Espere 100 milisegundos (std::this_thread::sleep_for). 3. Use la función de la Skill clearScreen() para limpiar la pantalla. 4. Actualice el tablero. Compila y ejecuta ./life para ver la simulación.
```
