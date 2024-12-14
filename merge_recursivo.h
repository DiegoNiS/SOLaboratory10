#ifndef MERGESORTRECURSIVO_H
#define MERGESORTRECURSIVO_H
#include <semaphore.h>

void merge_r(int *arr, int l, int m, int r);
void mergeSortRecursivo(int *v, int inicio, int fin, sem_t *);

#endif //MERGESORTRECURSIVO_H