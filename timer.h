#ifndef TIMER_H
#define TIMER_H

double tiempo_promedio(void (*sort_func)(int *, int, int, sem_t *), int *arr, int l, int r, sem_t *sem);

#endif
