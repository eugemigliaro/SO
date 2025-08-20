#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/* Lance varios procesos hijos desde un padre, haga que el padre cuelgue en un loop infinito sin hacer waitpid, mientras que sus hijos
terminan instantáneamente, salvo 1 que también quedará en un loop infinito.
Para observar el estado de los procesos se recomienda ejecutar
$ ps ax -O "%P"
1. ¿Qué imagina que va a pasar con los procesos hijos que terminaron? ¿Por qué cree que pasa?
2. Mate el proceso padre (kill) ¿Qué sucede?
3. ¿Cambió algo para el proceso hijo que estaba en un loop luego de matar al padre?
4. ¿Qué es el proceso init?
5. ¿Qué pasa en los sistemas POSIX con los procesos huérfanos? */

#define NUM_HIJOS 5

int main() {
    pid_t pid_padre = getpid();
    printf("Proceso padre iniciado (PID: %d)\n", pid_padre);
    printf("Creando %d procesos hijos...\n", NUM_HIJOS);
    
    for (int i = 0; i < NUM_HIJOS; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("Error en fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            if (i == 0) {
                printf("Hijo %d (PID: %d) - Quedará en loop infinito\n", i, getpid());
                while (1) {
                    sleep(10);
                }
            } else {
                printf("Hijo %d (PID: %d) - Terminaré inmediatamente\n", i, getpid());
                exit(0);
            }
        }
        else {
            printf("Padre: Creado hijo %d con PID %d\n", i, pid);
            sleep(1);
        }
    }
    
    printf("\nPadre: Todos los hijos creados. Entrando en loop infinito SIN waitpid()...\n");
    printf("Ejecuta 'ps ax -O \"%%P\"' en otra terminal para observar los estados\n");
    printf("Para matar el padre: kill %d\n", pid_padre);
    
    while (1) {
        sleep(30);
        printf("Padre (PID: %d) sigue vivo...\n", getpid());
    }
    
    return 0;
}

