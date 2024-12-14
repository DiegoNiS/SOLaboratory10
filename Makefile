CC = gcc
CFLAGS = -Wall
TARGET = main
OBJS = pruebas.o timer.o merge_recursivo.o merge_parallel.o

all: $(TARGET) grafica

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $@.c $^

pruebas.o: pruebas.c pruebas.h merge_recursivo.h merge_parallel.h timer.h
	$(CC) $(CFLAGS) -c pruebas.c

timer.o: timer.c timer.h
	$(CC) $(CFLAGS) -c timer.c

merge_recursivo.o: merge_recursivo.c merge_recursivo.h
	$(CC) $(CFLAGS) -c merge_recursivo.c

merge_parallel.o: merge_parallel.c merge_parallel.h
	$(CC) $(CFLAGS) -c merge_parallel.c

grafica: $(TARGET)
	./$(TARGET)
	gnuplot grafica.plt

clean:
	rm -f $(TARGET) $(OBJS) resultados.txt grafica.png