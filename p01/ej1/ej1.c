#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

/* Escribir un programa en C que liste recursivamente el contenido de un directorio que recibe como primer y único argumento, indicar si
cada elemento es un archivo o un directorio, tabular la salida por nivel de anidamiento (stat opendir readdir)
Ejemplo de la salida (solo a modo ilustrativo):
$./tree .
d   dir1
f   file1
d   dir3
f       file1
d       dir1
f           file1
f   file2 */

void list_directory(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];
    
    // Abrir el directorio
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    
    // Leer cada entrada del directorio
    while ((entry = readdir(dir)) != NULL) {
        // Saltar los directorios . y ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Crear el path completo
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        // Obtener información del archivo/directorio
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }
        
        // Verificar si es directorio o archivo e imprimir
        if (S_ISDIR(file_stat.st_mode)) {
            printf("d");
            // Imprimir la indentación según el nivel para el nombre
            for (int i = 0; i < depth; i++) {
                printf("    ");
            }
            printf("   %s\n", entry->d_name);
            // Llamada recursiva para listar el contenido del subdirectorio
            list_directory(full_path, depth + 1);
        } else {
            printf("f");
            // Imprimir la indentación según el nivel para el nombre
            for (int i = 0; i < depth; i++) {
                printf("    ");
            }
            printf("   %s\n", entry->d_name);
        }
    }
    
    closedir(dir);
}

int main(int argc, char *argv[]) {
    // Verificar que se haya proporcionado exactamente un argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <directorio>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Verificar que el argumento sea un directorio válido
    struct stat path_stat;
    if (stat(argv[1], &path_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    
    if (!S_ISDIR(path_stat.st_mode)) {
        fprintf(stderr, "Error: %s no es un directorio\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // Listar el contenido del directorio
    list_directory(argv[1], 0);
    
    return 0;
}