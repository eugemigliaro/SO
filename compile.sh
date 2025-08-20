#!/bin/bash

# Script de compilación para proyectos de SO
# Uso: ./compile.sh archivo.c [flags adicionales]

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Función para mostrar ayuda
show_help() {
    echo "Uso: $0 <archivo.c> [flags adicionales]"
    echo ""
    echo "Ejemplos:"
    echo "  $0 programa.c                    # Compila programa.c -> programa.exe"
    echo "  $0 programa.c -g                # Compila con información de debug"
    echo "  $0 programa.c -O2               # Compila con optimización"
    echo "  $0 *.c                          # Compila todos los archivos .c"
    echo ""
    echo "El script siempre usa flags básicos: -Wall -Wextra -std=c99"
}

# Verificar argumentos
if [ $# -eq 0 ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

# Flags básicos siempre incluidos
BASIC_FLAGS="-Wall -Wextra -std=c99"

# Función para compilar un archivo
compile_file() {
    local source_file="$1"
    shift
    local extra_flags="$@"
    
    # Obtener nombre sin extensión
    local base_name="${source_file%.c}"
    local output_file="${base_name}.exe"
    
    echo -e "${YELLOW}Compilando: ${source_file} -> ${output_file}${NC}"
    
    # Comando de compilación
    if gcc $BASIC_FLAGS $extra_flags -o "$output_file" "$source_file"; then
        echo -e "${GREEN}✓ Compilación exitosa: ${output_file}${NC}"
        
        # Hacer ejecutable (por si acaso)
        chmod +x "$output_file"
        
        return 0
    else
        echo -e "${RED}✗ Error compilando ${source_file}${NC}"
        return 1
    fi
}

# Procesar argumentos
source_files=()
extra_flags=()

for arg in "$@"; do
    if [[ "$arg" == *.c ]]; then
        source_files+=("$arg")
    else
        extra_flags+=("$arg")
    fi
done

# Verificar que hay archivos para compilar
if [ ${#source_files[@]} -eq 0 ]; then
    echo -e "${RED}Error: No se encontraron archivos .c${NC}"
    exit 1
fi

# Compilar cada archivo
success_count=0
total_count=${#source_files[@]}

echo -e "${YELLOW}Compilando ${total_count} archivo(s) con flags: ${BASIC_FLAGS} ${extra_flags[*]}${NC}"
echo ""

for source_file in "${source_files[@]}"; do
    if [ -f "$source_file" ]; then
        if compile_file "$source_file" "${extra_flags[@]}"; then
            ((success_count++))
        fi
    else
        echo -e "${RED}✗ Archivo no encontrado: ${source_file}${NC}"
    fi
    echo ""
done

# Resumen
echo "=============================="
echo -e "Compilados exitosamente: ${GREEN}${success_count}/${total_count}${NC}"

if [ $success_count -eq $total_count ]; then
    echo -e "${GREEN}¡Todas las compilaciones exitosas!${NC}"
    exit 0
else
    echo -e "${RED}Algunas compilaciones fallaron${NC}"
    exit 1
fi
