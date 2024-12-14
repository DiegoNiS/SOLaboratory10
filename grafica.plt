set terminal png
set output "grafica.png"
set title "Comparación de Tiempos de Merge Sort"
set xlabel "Tamaño del Arreglo"
set ylabel "Tiempo (segundos)"
set grid
set key outside
set xtics rotate by -45 # Rotar etiquetas si es necesario   
plot "resultados.txt" using 1:2 with lines title "Merge Sort Recursivo", \
     "resultados.txt" using 1:3 with lines title "Merge Sort Paralelo"
