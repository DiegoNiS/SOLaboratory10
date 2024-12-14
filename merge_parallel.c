#include "merge_parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void merge_p(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSortParallel(int *arr, int left, int right, sem_t *sem) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        pid_t left_pid, right_pid;

        if ((left_pid = fork()) == 0) {
            mergeSortParallel(arr, left, mid, sem);
            exit(0);
        }

        if ((right_pid = fork()) == 0) {
            mergeSortParallel(arr, mid + 1, right, sem);
            exit(0);
        }

        waitpid(left_pid, NULL, 0);
        waitpid(right_pid, NULL, 0);

        sem_wait(sem);
        merge_p(arr, left, mid, right);
        sem_post(sem);
    }
}

// #define SEM_NAME "/mergeR"
// int main(int argc, char *argv[]) {
//     int n;
//     if (argc < 2) {
//         printf("Usage: %s <size of array>\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }

//     n = atoi(argv[1]);
//     int *arr = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
//     if (arr == MAP_FAILED) {
//         perror("mmap");
//         exit(EXIT_FAILURE);
//     }

//     srand(time(NULL));
//     for (int i = 0; i < n; i++) {
//         arr[i] = rand() % 1000;
//     }

//     sem_t *sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
//     if (sem == SEM_FAILED) {
//         perror("sem_open");
//         exit(EXIT_FAILURE);
//     }

//     // Eliminar impresión del array
//     // printf("Array original:\n");
//     // for (int i = 0; i < n; i++) printf("%d ", arr[i]);
//     // printf("\n");

//     merge_sort(arr, 0, n - 1, sem);

//     // Eliminar impresión del array ordenado
//     // printf("Array ordenado:\n");
//     // for (int i = 0; i < n; i++) printf("%d ", arr[i]);
//     // printf("\n");

//     sem_close(sem);
//     sem_unlink(SEM_NAME);
//     munmap(arr, n * sizeof(int));

//     return 0;
// }
