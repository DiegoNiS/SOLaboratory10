#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include "timer.h"

double tiempo_promedio(void (*sort_func)(int *, int, int, sem_t*), int *arr, int l, int r, sem_t *sem) {
    clock_t start, end;
    start = clock(); // Captura del tiempo inicial
    sort_func(arr, l, r, sem); // Ejecución del algoritmo
    end = clock(); // Captura del tiempo final
    return (double)(end - start) / CLOCKS_PER_SEC; // Diferencia en segundos
}
