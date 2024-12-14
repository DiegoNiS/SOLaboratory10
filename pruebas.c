#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME "/mergeR"
#include "merge_recursivo.h"
#include "merge_parallel.h"
#include "timer.h"

void escribir_resultados(int tamano_arreglo, double time_rec, double time_proc) {
    FILE *file = fopen("resultados.txt", "a");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d %.6f %.6f\n", tamano_arreglo, time_rec, time_proc);
    fclose(file);
}

void comparar_tiempos(int tamano_arreglo){
    // printf("\nComparación de tiempos para un arreglo de tamaño %d:\n", tamano_arreglo);
    int arr[tamano_arreglo];
    int copy[tamano_arreglo];
    double time_rec, time_proc;

    for (int i = 0; i < tamano_arreglo; i++) {
        arr[i] = rand() % 10000;
    }

    sem_t *sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    memcpy(copy, arr, sizeof(arr));

    time_rec = tiempo_promedio(mergeSortRecursivo, arr, 0, tamano_arreglo - 1, sem);
    // printf("\tTiempo del Merge Sort Recursivo: %.6f segundos\n", time_rec);

    memcpy(copy, arr, sizeof(arr));
    time_proc = tiempo_promedio(mergeSortParallel, copy, 0, tamano_arreglo - 1, sem);
    // printf("\tTiempo del Merge Sort Paralelo con Procesos: %.6f segundos\n", time_proc);

    // printf("\n\tComparación de Tiempos:\n");
    // printf("\t- Merge Sort Recursivo: %.6f segundos\n", time_rec);
    // printf("\t- Merge Sort Paralelo: %.6f segundos\n", time_proc);

    // if (time_proc < time_rec) {
    //     printf("\n\tEl Merge Sort paralelo fue más rápido.\n");
    // } else {
    //     printf("\n\tEl Merge Sort recursivo fue más rápido.\n");
    // }

    escribir_resultados(tamano_arreglo, time_rec, time_proc);

    sem_close(sem);
    sem_unlink(SEM_NAME);
}
