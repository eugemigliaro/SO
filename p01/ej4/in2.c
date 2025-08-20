#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
Inciso 2: El proceso padre ejecuta p en background.
El programa c no participa en este ejercicio.
*/

int main() {
    pid_t pid_p;
    
    printf("Padre (PID: %d) iniciando...\n", getpid());
    
    // Fork para crear el proceso que ejecutará 'p' en background
    pid_p = fork();
    if (pid_p == -1) {
        perror("Error en fork para p");
        exit(EXIT_FAILURE);
    }
    
    if (pid_p == 0) {
        // Proceso hijo que ejecutará 'p'
        printf("Hijo P (PID: %d) ejecutando en background...\n", getpid());
        
        // Ejecutar el programa 'p'
        execve("./p", (char*[]){"./p", NULL}, NULL);
        
        // Si llegamos aquí, execve falló
        perror("Error ejecutando p");
        exit(EXIT_FAILURE);
    }
    
    // Proceso padre continúa sin esperar al hijo (background)
    printf("Padre: Proceso P (PID: %d) lanzado en background\n", pid_p);
    printf("Padre: Continuando con otras tareas mientras P ejecuta...\n");
    
    // Simular que el padre hace otras cosas
    for (int i = 0; i < 3; i++) {
        printf("Padre: Trabajando... (%d)\n", i + 1);
        sleep(2);
    }
    
    printf("Padre: Terminé mi trabajo. El proceso P puede seguir ejecutándose.\n");
    printf("Padre: Finalizando (P queda huérfano y será adoptado por init)\n");
    
    return 0;
}