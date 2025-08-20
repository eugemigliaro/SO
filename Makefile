# Makefile para compilación automática con extensiones .exe
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Buscar todos los archivos .c automáticamente
SOURCES = $(wildcard p01/ej*/*.c)
EXECUTABLES = $(SOURCES:.c=.exe)

# Regla por defecto
all: $(EXECUTABLES)

# Regla para compilar cualquier .c a .exe
%.exe: %.c
	@echo "Compilando: $< -> $@"
	$(CC) $(CFLAGS) -o $@ $<
	@echo "✓ Compilación exitosa: $@"

# Compilación con debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXECUTABLES)

# Compilación optimizada
release: CFLAGS += $(RELEASE_FLAGS)
release: $(EXECUTABLES)

# Limpiar archivos compilados
clean:
	@echo "Limpiando archivos compilados..."
	find . -name "*.exe" -type f -delete
	find . -name "*.o" -type f -delete
	find . -name "output.txt" -type f -delete
	@echo "✓ Limpieza completada"

# Compilar solo un ejercicio específico
ej1: p01/ej1/ej1.exe

ej2: p01/ej2/padre.exe p01/ej2/hijo.exe

ej3: p01/ej3/ej3.exe

ej4: p01/ej4/p.exe p01/ej4/c.exe p01/ej4/in1.exe p01/ej4/in2.exe p01/ej4/in3.exe p01/ej4/in4.exe

# Mostrar ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make          - Compilar todos los archivos"
	@echo "  make debug    - Compilar con información de debug"
	@echo "  make release  - Compilar con optimizaciones"
	@echo "  make ej1      - Compilar solo ejercicio 1"
	@echo "  make ej2      - Compilar solo ejercicio 2"
	@echo "  make ej3      - Compilar solo ejercicio 3"
	@echo "  make ej4      - Compilar solo ejercicio 4"
	@echo "  make clean    - Limpiar archivos compilados"
	@echo "  make help     - Mostrar esta ayuda"

# Indicar que estos targets no son archivos
.PHONY: all debug release clean help ej1 ej2 ej3 ej4
