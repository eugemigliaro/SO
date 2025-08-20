#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

/*
Programa hijo que será ejecutado por cada proceso hijo creado por el padre.
Cada hijo:
1. Imprime su propio PID
2. Duerme una cantidad aleatoria de tiempo (1-5 segundos)
3. Termina
*/

int main() {
    pid_t mi_pid = getpid();
    
    // Inicializar el generador de números aleatorios con el PID
    // para que cada proceso tenga una semilla diferente
    srand(time(NULL) + mi_pid);
    
    // Generar tiempo aleatorio entre 1 y 5 segundos
    int tiempo_sleep = (rand() % 5) + 1;
    
    printf("  Hijo (PID: %d) iniciado. Dormiré por %d segundos...\n", mi_pid, tiempo_sleep);
    
    // Dormir por el tiempo aleatorio
    sleep(tiempo_sleep);
    
    printf("  Hijo (PID: %d) terminando después de dormir %d segundos.\n", mi_pid, tiempo_sleep);
    
    return 0;
}
