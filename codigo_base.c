#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- 1. ESTRUCTURAS DE DATOS ---
typedef struct {
    double cifra_descuento; 
    char operador[150];
    char nombre_plan[150];
} PlanDescuento;

typedef struct {
    int id;
    char nombre[20];
    double tiempo;
    unsigned long long operaciones;
} ResultadoAlgo;

// --- 2. VARIABLES GLOBALES PARA INSTRUMENTALIZACIÓN ---
unsigned long long operaciones_basicas = 0;

// --- 3. PROTOTIPOS DE ALGORITMOS ---
// Obligatorios
void burbuja(PlanDescuento arr[], int n);
void seleccion(PlanDescuento arr[], int n);
void insercion(PlanDescuento arr[], int n);
void merge_sort(PlanDescuento arr[], int left, int right);
void merge(PlanDescuento arr[], int left, int center, int right);
void quick_sort(PlanDescuento arr[], int left, int right);
int split(PlanDescuento arr[], int left, int right);

// Extras
void bubble_down(PlanDescuento arr[], int i, int n);
void heap_sort(PlanDescuento arr[], int n);
void shell_sort(PlanDescuento arr[], int n);

// Funciones auxiliares
void copiar_array(PlanDescuento origen[], PlanDescuento destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

int parse_line(char* line, char* fields[]) {
    int count = 0, in_quotes = 0;
    char* ptr = line;
    fields[count++] = ptr;
    
    while (*ptr) {
        if (*ptr == '"') {
            in_quotes = !in_quotes;
        } else if (*ptr == ',' && !in_quotes) {
            *ptr = '\0';
            fields[count++] = ptr + 1;
        }
        ptr++;
    }
    
    if (count > 0) {
        char* last_field = fields[count - 1];
        int len = strlen(last_field);
        if (len > 0 && (last_field[len - 1] == '\n' || last_field[len - 1] == '\r')) {
            last_field[len - 1] = '\0';
            if (len > 1 && (last_field[len - 2] == '\n' || last_field[len - 2] == '\r')) {
                last_field[len - 2] = '\0';
            }
        }
    }
    return count;
}

// --- MAIN ---
int main() {
    PlanDescuento datos_originales[1000];
    int total_datos = 0;

    FILE* file = fopen("planesDescuento.csv", "r");
    if (!file) {
        printf("Error: No se encontro 'planesDescuento.csv' en la carpeta.\n");
        return 1;
    }

    char line[1024];
    int row_count = 0;

    while (fgets(line, sizeof(line), file)) {
        row_count++;
        if (row_count <= 2) continue;

        char* fields[10];
        int num_fields = parse_line(line, fields);

        if (num_fields >= 6 && strstr(fields[5], "euro en cada litro") != NULL) {
            datos_originales[total_datos].cifra_descuento = atof(fields[4]);
            strncpy(datos_originales[total_datos].operador, fields[0], 149);
            strncpy(datos_originales[total_datos].nombre_plan, fields[1], 149);
            total_datos++;
        }
    }
    fclose(file);

    printf("Se cargaron %d registros filtrados correctamente.\n\n", total_datos);
    if (total_datos == 0) {
        printf("No se encontraron registros validos.\n");
        return 1;
    }

    PlanDescuento datos_prueba[1000];
    clock_t inicio, fin;
    ResultadoAlgo ranking[7];

    printf("==============================================================\n");
    printf("   EVALUACION DE ALGORITMOS DE ORDENACION (N = %d)\n", total_datos);
    printf("==============================================================\n");

    // --- 1. BURBUJA ---
    ranking[0].id = 0; strcpy(ranking[0].nombre, "Burbuja");
    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0; inicio = clock();
    burbuja(datos_prueba, total_datos);
    fin = clock();
    ranking[0].tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    ranking[0].operaciones = operaciones_basicas;

    // --- 2. SELECCIÓN ---
    ranking[1].id = 1; strcpy(ranking[1].nombre, "Seleccion");
    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0; inicio = clock();
    seleccion(datos_prueba, total_datos);
    fin = clock();
    ranking[1].tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    ranking[1].operaciones = operaciones_basicas;

    // --- 3. INSERCIÓN ---
    ranking[2].id = 2; strcpy(ranking[2].nombre, "Insercion");
    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0; inicio = clock();
    insercion(datos_prueba, total_datos);
    fin = clock();
    ranking[2].tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    ranking[2].operaciones = operaciones_basicas;

    // --- 4. MERGESORT ---
    ranking[3].id = 3; strcpy(ranking[3].nombre, "MergeSort");
    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0; inicio = clock();
    merge_sort(datos_prueba, 0, total_datos - 1);
    fin = clock();
    ranking[3].tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    ranking[3].operaciones = operaciones_basicas;

    // --- 5. QUICKSORT ---
    ranking[4].id = 4; strcpy(ranking[4].nombre, "QuickSort");
    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0; inicio = clock();
    quick_sort(datos_prueba, 0, total_datos - 1);
    fin = clock();
    ranking[4].tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    ranking[4].operaciones = operaciones_basicas;

    // --- 6. HEAPSORT (Extra) ---
    ranking[5].id = 5; strcpy(ranking[5].nombre, "HeapSort (Extra)");
    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0; inicio = clock();
    heap_sort(datos_prueba, total_datos);
    fin = clock();
    ranking[5].tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    ranking[5].operaciones = operaciones_basicas;

    // --- 7. SHELLSORT (Extra) ---
    ranking[6].id = 6; strcpy(ranking[6].nombre, "ShellSort(Extra)");
    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0; inicio = clock();
    shell_sort(datos_prueba, total_datos);
    fin = clock();
    ranking[6].tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    ranking[6].operaciones = operaciones_basicas;


    // --- ORDENAR EL RANKING (De mejor a peor) ---
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6 - i; j++) {
            int swap = 0;
            // Tiempo
            if (ranking[j].tiempo > ranking[j+1].tiempo) {
                swap = 1;
            } 
            // Operaciones basicas
            else if (ranking[j].tiempo == ranking[j+1].tiempo && ranking[j].operaciones > ranking[j+1].operaciones) {
                swap = 1;
            }
            if (swap) {
                ResultadoAlgo temp = ranking[j];
                ranking[j] = ranking[j+1];
                ranking[j+1] = temp;
            }
        }
    }

    // Imprimir Ranking
    printf("%-5s | %-16s | %-15s | %-20s\n", "Pos", "Algoritmo", "Tiempo (seg)", "Operaciones Basicas");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < 7; i++) {
        printf("#%-4d | %-16s | %-15.6f | %-20llu\n", i+1, ranking[i].nombre, ranking[i].tiempo, ranking[i].operaciones);
    }

    // --- PRUEBA FINAL CON EL GANADOR ---
    printf("\n==============================================================\n");
    printf("   EJECUCION FINAL: EL GANADOR ES %s\n", ranking[0].nombre);
    printf("==============================================================\n");

    copiar_array(datos_originales, datos_prueba, total_datos);
    operaciones_basicas = 0;
    inicio = clock();

    switch (ranking[0].id) {
        case 0: burbuja(datos_prueba, total_datos); break;
        case 1: seleccion(datos_prueba, total_datos); break;
        case 2: insercion(datos_prueba, total_datos); break;
        case 3: merge_sort(datos_prueba, 0, total_datos - 1); break;
        case 4: quick_sort(datos_prueba, 0, total_datos - 1); break;
        case 5: heap_sort(datos_prueba, total_datos); break;
        case 6: shell_sort(datos_prueba, total_datos); break;
    }

    fin = clock();
    double tiempo_final = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    printf("%-15s | %-15s | %-20s\n", "Ejecucion", "Tiempo (seg)", "Operaciones");
    printf("--------------------------------------------------------------\n");
    printf("%-15s | %-15.6f | %-20llu\n", "ADAPTATIVO", tiempo_final, operaciones_basicas);

    printf("\n--- Primeros 5 resultados ordenados ---\n");
    for(int i = 0; i < 5 && i < total_datos; i++){
        printf("%.3f ctms - %s (%s)\n", datos_prueba[i].cifra_descuento, datos_prueba[i].operador, datos_prueba[i].nombre_plan);
    }
    printf("==============================================================\n");

    return 0;
}

// --- IMPLEMENTACIÓN DE ALGORITMOS OBLIGATORIOS ---

void burbuja(PlanDescuento arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            operaciones_basicas++;
            if (arr[j].cifra_descuento > arr[j + 1].cifra_descuento) {
                PlanDescuento temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void seleccion(PlanDescuento arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            operaciones_basicas++;
            if (arr[j].cifra_descuento < arr[min_index].cifra_descuento) {
                min_index = j;
            }
        }
        if (min_index != i) {
            PlanDescuento temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

void insercion(PlanDescuento arr[], int n) {
    for (int i = 1; i < n; i++) {
        PlanDescuento value = arr[i];
        int pos = i;
        
        operaciones_basicas++; 
        while (pos > 0 && value.cifra_descuento < arr[pos - 1].cifra_descuento) {
            arr[pos] = arr[pos - 1];
            pos--;
            if(pos > 0) operaciones_basicas++; 
        }
        arr[pos] = value;
    }
}

void merge(PlanDescuento arr[], int left, int center, int right) {
    int size = right - left + 1;
    PlanDescuento* buffer = (PlanDescuento*)malloc(size * sizeof(PlanDescuento));
    int a = left;
    int b = center + 1;
    int m = 0;

    while (a <= center && b <= right) {
        operaciones_basicas++; 
        if (arr[a].cifra_descuento <= arr[b].cifra_descuento) {
            buffer[m++] = arr[a++];
        } else {
            buffer[m++] = arr[b++];
        }
    }

    while (a <= center) {
        operaciones_basicas++;
        buffer[m++] = arr[a++];
    }
    while (b <= right) {
        operaciones_basicas++; 
        buffer[m++] = arr[b++];
    }

    for (int i = 0; i < size; i++) {
        arr[left + i] = buffer[i];
    }
    free(buffer);
}

void merge_sort(PlanDescuento arr[], int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        merge_sort(arr, left, center);
        merge_sort(arr, center + 1, right);
        merge(arr, left, center, right);
    }
}

int split(PlanDescuento arr[], int left, int right) {
    double splitter_value = arr[left].cifra_descuento;
    int i = left + 1;
    int j = right;

    do {
        operaciones_basicas++;
        while (i <= j && arr[i].cifra_descuento <= splitter_value) {
            i++;
            if (i <= j) operaciones_basicas++;
        }
        operaciones_basicas++;
        while (j >= i && arr[j].cifra_descuento > splitter_value) {
            j--;
            if (j >= i) operaciones_basicas++;
        }

        if (i < j) {
            PlanDescuento temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } while (i < j);

    if (j > left) {
        PlanDescuento temp = arr[left];
        arr[left] = arr[j];
        arr[j] = temp;
    }
    return j;
}

void quick_sort(PlanDescuento arr[], int left, int right) {
    if (left < right) {
        int i = split(arr, left, right);
        quick_sort(arr, left, i - 1);
        quick_sort(arr, i + 1, right);
    }
}

// --- IMPLEMENTACIÓN DE ALGORITMOS EXTRAS ---

// HEAPSORT
void bubble_down(PlanDescuento arr[], int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    operaciones_basicas++;
    if (left < n && arr[left].cifra_descuento > arr[largest].cifra_descuento) {
        largest = left;
    }

    operaciones_basicas++;
    if (right < n && arr[right].cifra_descuento > arr[largest].cifra_descuento) {
        largest = right;
    }

    if (largest != i) {
        PlanDescuento temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        bubble_down(arr, largest, n);
    }
}

void heap_sort(PlanDescuento arr[], int n) {
    // Construye el Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        bubble_down(arr, i, n);
    }
    // Extraer del Heap
    for (int i = n - 1; i > 0; i--) {
        PlanDescuento temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        bubble_down(arr, 0, i);
    }
}

// SHELLSORT
void shell_sort(PlanDescuento arr[], int n) {
    // Comienza con un hueco (gap) grande y lo reduce en cada paso
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            PlanDescuento temp = arr[i];
            int j;
            
            operaciones_basicas++; 
            for (j = i; j >= gap && arr[j - gap].cifra_descuento > temp.cifra_descuento; j -= gap) {
                arr[j] = arr[j - gap];
                if (j - gap >= gap) operaciones_basicas++; 
            }
            arr[j] = temp;
        }
    }
}