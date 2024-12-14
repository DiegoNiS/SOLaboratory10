#ifndef MERGEPARALLEL_H
#define MERGEPARALLEL_H
#include <semaphore.h>

void merge_p(int *, int, int, int);
void mergeSortParallel(int *, int, int, sem_t *);

#endif