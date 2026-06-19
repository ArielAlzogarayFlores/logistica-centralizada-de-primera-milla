# Logística centralizada de primera milla

Trabajo Práctico N°2 de la materia **Tecnología Digital V: Diseño de algoritmos** — Licenciatura en Tecnología Digital, Universidad Torcuato Di Tella (1er semestre 2026).

El trabajo aborda el problema de asignación de vendedores a depósitos de la red de **ThunderPack**, modelado como una instancia del **Problema de Asignación Generalizada (GAP, Generalized Assignment Problem)**: dado un conjunto de vendedores `N` y un conjunto de depósitos `M` con capacidades limitadas, se busca asignar cada vendedor a exactamente un depósito, respetando las capacidades y minimizando la distancia total recorrida. El enunciado completo se encuentra en [`enunciado.pdf`](./enunciado.pdf).

## Estructura del repositorio

```
.
├── enunciado.pdf            # Consigna del TP
├── informe/                 # Informe del trabajo (modelo, experimentación, resultados, conclusiones)
├── resultados/               # Salidas/resultados de la experimentación
└── src/                      # Código fuente (C++)
    ├── main.cpp               # Punto de entrada del programa
    ├── Makefile                # Build del proyecto
    ├── heuristicas/             # Heurísticas constructivas para el GAP
    ├── busqueda-local/          # Operadores de búsqueda local
    ├── metaheuristicas/         # Metaheurística (GRASP / similar) — en desarrollo
    ├── utils/                   # Lectura/escritura de instancias, modelo de datos y runner de algoritmos
    ├── instances/                # Instancias de benchmark y la instancia real de ThunderPack
    │   ├── gap/                   # Instancias de benchmark de la literatura (gap_a, gap_b, gap_e, ...)
    │   └── real/                  # Instancia real (n=1100 vendedores, m=310 depósitos) + JSON con geolocalización
    └── output/                   # Carpeta donde se vuelcan las soluciones generadas
```

## El modelo

Cada depósito $i \in M$ tiene una capacidad máxima $c_i$. Cada vendedor $j \in N$ tiene una demanda $d_{ij}$ y un costo $c_{ij}$ (en nuestro caso, la distancia a recorrer) si es asignado al depósito $i$. Una solución es una partición $\Gamma_1, \ldots, \Gamma_m$ de $N$ que:

1. asigna cada vendedor a exactamente un depósito,
2. respeta la capacidad de cada depósito $\sum_{j \in \Gamma_i} d_{ij} \le c_i$
3. minimiza el costo total $\sum_i \sum_{j \in \Gamma_i} c_{ij}$

Si una solución deja vendedores sin asignar, se penaliza con $3 \times c_{\max}$ por cada vendedor no asignado, donde:

$$
c_{\max} = \max_{i,j} c_{ij}
$$

## Algoritmos implementados

- **Heurísticas constructivas** (`src/heuristicas/`): cinco heurísticas distintas para construir soluciones factibles (entre ellas, heurísticas tipo *vecino más cercano* orientadas por vendedor y por depósito).
- **Operadores de búsqueda local** (`src/busqueda-local/`): operadores de mejora sobre una solución inicial (`swap` entre vendedores asignados a distintos depósitos y `relocate` de un vendedor a otro depósito), aplicados con estrategia *first improvement*.
- **Metaheurística** (`src/metaheuristicas/`): en desarrollo.

El detalle de diseño, justificación y resultados experimentales de cada método se encuentra en el [informe](./informe).

## Compilación

### Requisitos previos

- Compilador `g++` con soporte de **C++17** (probado con GCC ≥ 9).
- `make`.
- Sistema operativo tipo Unix (Linux / macOS, o WSL en Windows). El `Makefile` no fue probado en entornos nativos de Windows.

### Build

```bash
cd src
make
```

Esto compila todos los fuentes (`main.cpp`, `utils/`, `heuristicas/`, `busqueda-local/`) y genera el ejecutable `gap_simulator` dentro de `src/`.

Para limpiar los binarios y objetos generados:

```bash
make clean
```

## Ejecución

> **Importante**: todos los comandos siguientes se ejecutan **desde la carpeta `src/`**, que es donde queda el ejecutable `gap_simulator`. Los paths de `<input>` y `<output>` son relativos a esa misma carpeta.

```bash
./gap_simulator <input> <output> <algoritmo>
```

- `<input>`: ruta al archivo de la instancia a resolver (formato de texto plano del dataset de benchmark del GAP). Las instancias provistas están en `instances/gap/` (benchmark) e `instances/real/` (instancia real de ThunderPack).
- `<output>`: nombre del archivo donde se escribe la solución. **No es una ruta**: el programa siempre lo guarda dentro de `src/output/`, sin importar el path que se le pase (por ejemplo, `gap_a_1_sol.txt` se guarda como `output/gap_a_1_sol.txt`).
- `<algoritmo>`: algoritmo a ejecutar. Valores soportados actualmente:
  - `heuristica_1`, `heuristica_2`, `heuristica_3`, `heuristica_4`, `heuristica_5`
  - `operador_1`, `operador_2`

Si se invoca con menos de 3 argumentos, el programa no ejecuta nada y muestra por terminal el modo de uso:

```
Uso:
./gap_simulator <input> <output> <algoritmo>
```

Si el archivo de instancia no existe, no se puede leer, o el `<algoritmo>` indicado no es ninguno de los listados arriba, el programa corta la ejecución y muestra el error correspondiente por terminal (por ejemplo, `ERROR: Algoritmo inexistente`).

### Ejemplos

Resolver una instancia de benchmark con una heurística constructiva:

```bash
./gap_simulator instances/gap/gap_a/gap_a_1.txt gap_a_1_sol.txt heuristica_2
```

Resolver la instancia real de ThunderPack (1100 vendedores, 310 depósitos) con un operador de búsqueda local:

```bash
./gap_simulator instances/real/real_instance real_sol.txt operador_1
```

> Nota: por su tamaño, la instancia real puede tardar notablemente más en resolverse que las instancias de benchmark (que suelen ser de decenas a pocos cientos de vendedores/depósitos), sobre todo con los operadores de búsqueda local.

### Salidas del programa

La ejecución produce **dos salidas distintas**:

1. **Por terminal**: un resumen breve de la corrida — confirmación de lectura de la instancia, cantidad de depósitos y vendedores de la instancia, el valor de `c_max` calculado, y la ruta del archivo de salida generado.

2. **Archivo de output** (`src/output/<output>`): contiene el detalle completo de la solución, con el siguiente formato:

   ```
   Instancia: <input>
   Algoritmo: <algoritmo>
   Costo total: <costo_total>
   Solución parcial: SÍ|NO
   Cantidad de depósitos: <m>
   Cantidad de vendedores (sin asignar)/asignados: (<vendedores_sin_asignar>)/<n>   # solo si la solución es parcial
   Depósito (0): <vendedores asignados al depósito 0, separados por espacio>
   Depósito (1): <vendedores asignados al depósito 1, separados por espacio>
   ...
   Depósito (m-1): <vendedores asignados al depósito m-1, separados por espacio>
   ```

   Es decir, además de la lista de asignaciones por depósito (una línea por depósito, con los índices de los vendedores asignados a cada uno), el archivo incluye metadata de la corrida: instancia utilizada, algoritmo ejecutado, costo total de la solución (incluyendo la penalización por vendedores sin asignar, si corresponde), si la solución es parcial, y —en ese caso— cuántos vendedores quedaron sin asignar.

## Instancias

- **Benchmark**: instancias clásicas de la literatura del GAP (`src/instances/gap/`), usadas para comparar el desempeño de los algoritmos.
- **Instancia real**: instancia de ThunderPack con 1100 vendedores y 310 depósitos (`src/instances/real/`), que además incluye un archivo JSON con la geolocalización de vendedores y depósitos para su visualización.

## Informe

El informe con la descripción del modelo, las decisiones de diseño, la experimentación realizada y el análisis del caso real de ThunderPack se encuentra en la carpeta [`informe/`](./informe).
