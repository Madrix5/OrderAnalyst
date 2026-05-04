# 📊 Evaluador de Algoritmos de Ordenación en C

Este repositorio contiene un programa escrito en C diseñado para cargar datos desde un archivo CSV, filtrarlos según un criterio específico y evaluar el rendimiento de varios algoritmos de ordenación clásicos. 

El programa no solo ordena los datos, sino que realiza una **instrumentalización** midiendo tanto el **tiempo de ejecución** (en segundos) como el **número de operaciones básicas** (comparaciones e intercambios), generando finalmente un ranking del mejor al peor algoritmo para el conjunto de datos proporcionado.

---

## 🚀 Características Principales

*   **Parseo de CSV:** Incluye una función robusta para leer archivos CSV teniendo en cuenta campos delimitados por comillas.
*   **Filtrado de Datos:** Selecciona automáticamente los registros que contienen la frase `"euro en cada litro"`.
*   **Benchmarking Automático:** Evalúa y compara 7 algoritmos de ordenación diferentes.
*   **Ranking Dinámico:** Ordena los resultados de las pruebas basándose primero en el tiempo de ejecución y, en caso de empate, en el número de operaciones básicas.

---

## 🧠 Algoritmos Implementados

El programa pone a prueba los siguientes algoritmos de ordenación:

**Obligatorios:**
1.  **Burbuja** (Bubble Sort)
2.  **Selección** (Selection Sort)
3.  **Inserción** (Insertion Sort)
4.  **MergeSort** (Ordenamiento por Mezcla)
5.  **QuickSort** (Ordenamiento Rápido)

**Extras:**
6.  **HeapSort** (Ordenamiento por Montículos)
7.  **ShellSort** (Ordenamiento de Shell)

---

## 📂 Estructura de Datos

El programa utiliza una estructura principal `PlanDescuento` para almacenar la información relevante de cada fila del CSV:
```c
typedef struct {
    double cifra_descuento; // Valor por el cual se ordenan los datos
    char operador[150];
    char nombre_plan[150];
} PlanDescuento;
```

---

## 🛠️ Requisitos

*   Un compilador de C (como `gcc` o `clang`).
*   Un archivo llamado `planesDescuento.csv` en el mismo directorio que el ejecutable. Este archivo debe contener al menos 6 columnas, donde la columna 5 contiene la cifra de descuento y la columna 6 contiene la descripción del plan.

---

## ⚙️ Instalación y Uso

1. **Clona el repositorio:**
   ```bash
   git clone [https://github.com/tu-usuario/tu-repositorio.git](https://github.com/tu-usuario/tu-repositorio.git)
   cd tu-repositorio
   ```

2. **Asegúrate de tener el archivo de datos:**
   Coloca tu archivo `planesDescuento.csv` en la raíz de la carpeta del proyecto.

3. **Compila el código:**
   Usando `gcc`, puedes compilar el programa con el siguiente comando:
   ```bash
   gcc main.c -o evaluador_ordenacion
   ```

4. **Ejecuta el programa:**
   ```bash
   ./evaluador_ordenacion
   ```

---

## 📋 Ejemplo de Salida Esperada

Al ejecutar el programa, verás por consola un resumen con el número de registros cargados, seguido de una tabla comparativa y una demostración final con el algoritmo ganador:
```text
Se cargaron X registros filtrados correctamente.

==============================================================
   EVALUACION DE ALGORITMOS DE ORDENACION (N = X)
==============================================================
Pos   | Algoritmo        | Tiempo (seg)    | Operaciones Basicas 
-----------------------------------------------------------------
#1    | QuickSort        | 0.000120        | 4500                
#2    | MergeSort        | 0.000150        | 5200                
...
#7    | Burbuja          | 0.045000        | 499500              

==============================================================
   EJECUCION FINAL: EL GANADOR ES QuickSort
==============================================================
...
```

---

## 🤝 Contribuciones
¡Las contribuciones son bienvenidas! Si deseas mejorar la precisión del temporizador, añadir nuevos algoritmos (como Radix Sort) o mejorar el parseo del CSV, siéntete libre de abrir una *Pull Request*.
