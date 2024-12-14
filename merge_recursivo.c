#include "merge_recursivo.h"
#include <stdlib.h>

// implementacion del metodo recursivo de mergeSort
void mergeSortRecursivo(int *v, int inicio, int fin, sem_t *sem) {
    if (inicio < fin) {
        int mitad = (inicio + fin) / 2;
        mergeSortRecursivo(v, inicio, mitad, sem);
        mergeSortRecursivo(v, mitad + 1, fin, sem);
        merge_r(v, inicio, mitad, fin);
    }
}

/* 
implementacion del metodo merge que ordena 
por mitades y une las mitades ordenadas
*/
void merge_r(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}