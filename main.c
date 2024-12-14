#include "pruebas.h"
#include <stdio.h>

int main() {
    // Borrar el contenido del archivo de resultados al inicio
    FILE *file = fopen("resultados.txt", "w");
    if (file != NULL) {
        fclose(file);
    }

    int final = 100000;
    int first = 0;
    int n = 40;
    int step = (final - first) / n;

    //crear varias pruebas con diferentes tamaños de arreglos
    for (int i = first + step; i <= final; i += step) {
        comparar_tiempos(i);
    }

    return 0;
}
