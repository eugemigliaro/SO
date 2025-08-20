#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
Ejercicio 2:
1. Escribir un programa en C que lance 10 procesos que realicen alguna tarea que dure una cierta cantidad de tiempo considerable
   (por ejemplo, dormir una cantidad al azar de tiempo), el programa debe esperar a que sus procesos hijos terminen para terminar
   él mismo. (fork waitpid).
2. Hacer que cada hijo imprima su propio pid (getpid)
3. Separe el código de los hijos y del padre en dos unidades de compilación diferentes (execve)
*/

#define NUM_HIJOS 10

int main() {
    pid_t pids_hijos[NUM_HIJOS];
    int i;

    printf("Proceso padre (PID: %d) iniciando...\n", getpid());
    printf("Creando %d procesos hijos...\n\n", NUM_HIJOS);
    
    // Crear 10 procesos hijos
    for (i = 0; i < NUM_HIJOS; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            // Error en fork
            perror("Error en fork");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) {
            // Código del proceso hijo
            // Usar execve para ejecutar el programa hijo
            char *args[] = {"./hijo", NULL};
            char *env[] = {NULL};
            
            execve("./hijo", args, env);
            
            // Si llegamos aquí, execve falló
            perror("Error en execve");
            exit(EXIT_FAILURE);
        } 
        else {
            // Código del proceso padre
            pids_hijos[i] = pid;
            printf("Padre: Creado proceso hijo %d con PID %d\n", i + 1, pid);
        }
    }
    
    printf("\nPadre: Todos los hijos creados. Esperando a que terminen...\n\n");
    
    // Esperar a que todos los hijos terminen
    for (i = 0; i < NUM_HIJOS; i++) {
        int status;
        pid_t pid_terminado = waitpid(pids_hijos[i], &status, 0);
        
        if (pid_terminado == -1) {
            perror("Error en waitpid");
        } else {
            printf("Padre: El hijo con PID %d ha terminado\n", pid_terminado);
        }
    }
    printf("\nPadre: Todos los hijos han terminado. Finalizando programa.\n");
    return 0;
}
