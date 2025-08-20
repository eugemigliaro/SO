#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
Inciso 1: El proceso padre ejecuta p y c (fork y exec) conectando el
stdout de p al stdin de c utilizando un pipe.
*/

int main() {
    int pipefd[2];
    pid_t pid_p, pid_c;
    
    printf("Padre (PID: %d) iniciando...\n", getpid());
    
    // Crear el pipe
    if (pipe(pipefd) == -1) {
        perror("Error creando pipe");
        exit(EXIT_FAILURE);
    }
    
    // Fork para crear el proceso que ejecutará 'p' (productor)
    pid_p = fork();
    if (pid_p == -1) {
        perror("Error en fork para p");
        exit(EXIT_FAILURE);
    }
    
    if (pid_p == 0) {
        // Proceso hijo que ejecutará 'p'
        printf("Hijo P (PID: %d) iniciando...\n", getpid());
        
        // Cerrar el extremo de lectura del pipe (no lo necesitamos)
        close(pipefd[0]);
        
        // Redirigir stdout al extremo de escritura del pipe
        dup2(pipefd[1], STDOUT_FILENO);
        
        // Cerrar el descriptor original del pipe
        close(pipefd[1]);
        
        // Ejecutar el programa 'p'
        execve("./p", (char*[]){"./p", NULL}, NULL);
        
        // Si llegamos aquí, execve falló
        perror("Error ejecutando p");
        exit(EXIT_FAILURE);
    }
    
    // Fork para crear el proceso que ejecutará 'c' (consumidor)
    pid_c = fork();
    if (pid_c == -1) {
        perror("Error en fork para c");
        exit(EXIT_FAILURE);
    }
    
    if (pid_c == 0) {
        // Proceso hijo que ejecutará 'c'
        printf("Hijo C (PID: %d) iniciando...\n", getpid());
        
        // Cerrar el extremo de escritura del pipe (no lo necesitamos)
        close(pipefd[1]);
        
        // Redirigir stdin al extremo de lectura del pipe
        dup2(pipefd[0], STDIN_FILENO);
        
        // Cerrar el descriptor original del pipe
        close(pipefd[0]);
        
        // Ejecutar el programa 'c'
        execve("./c", (char*[]){"./c", NULL}, NULL);
        
        // Si llegamos aquí, execve falló
        perror("Error ejecutando c");
        exit(EXIT_FAILURE);
    }
    
    // Proceso padre: cerrar ambos extremos del pipe
    // (los hijos ya tienen sus copias)
    close(pipefd[0]);
    close(pipefd[1]);
    
    printf("Padre: Hijos creados. P (PID: %d), C (PID: %d)\n", pid_p, pid_c);
    printf("Padre: Esperando a que terminen los procesos...\n");
    
    // Esperar a que terminen ambos hijos
    int status;
    waitpid(pid_p, &status, 0);
    printf("Padre: Proceso P terminó\n");
    
    waitpid(pid_c, &status, 0);
    printf("Padre: Proceso C terminó\n");
    
    printf("Padre: Todos los procesos terminaron. Finalizando.\n");
    return 0;
}