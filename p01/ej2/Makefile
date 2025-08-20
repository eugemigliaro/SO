# Makefile para el ejercicio 2
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Compilar ambos programas
all: padre hijo

padre: padre.c
	$(CC) $(CFLAGS) -o padre padre.c

hijo: hijo.c
	$(CC) $(CFLAGS) -o hijo hijo.c

# Limpiar archivos compilados
clean:
	rm -f padre hijo

# Ejecutar el programa
run: all
	./padre

.PHONY: all clean run
