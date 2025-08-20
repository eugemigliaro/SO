#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

/*
Inciso 3: El proceso padre ejecuta p y redirecciona stdout a un archivo.
(close y open). El programa c no participa en este ejercicio.
*/

int main() {
    pid_t pid_p;
    
    printf("Padre (PID: %d) iniciando...\n", getpid());
    
    // Fork para crear el proceso que ejecutará 'p'
    pid_p = fork();
    if (pid_p == -1) {
        perror("Error en fork para p");
        exit(EXIT_FAILURE);
    }
    
    if (pid_p == 0) {
        // Proceso hijo que ejecutará 'p'
        printf("Hijo P (PID: %d) redirigiendo stdout a archivo...\n", getpid());
        
        // Cerrar stdout
        close(STDOUT_FILENO);
        
        // Abrir archivo para escritura (se convierte en el nuevo stdout)
        int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error abriendo archivo output.txt");
            exit(EXIT_FAILURE);
        }
        
        // Verificar que el archivo se abrió en el descriptor STDOUT_FILENO
        if (fd != STDOUT_FILENO) {
            fprintf(stderr, "Error: el archivo no se abrió como stdout\n");
            exit(EXIT_FAILURE);
        }
        
        printf("Redirección configurada. Ejecutando programa p...\n");
        
        // Ejecutar el programa 'p' (su salida irá al archivo)
        execve("./p", (char*[]){"./p", NULL}, NULL);
        
        // Si llegamos aquí, execve falló
        perror("Error ejecutando p");
        exit(EXIT_FAILURE);
    }
    
    // Proceso padre espera a que termine el hijo
    printf("Padre: Proceso P (PID: %d) ejecutándose con salida redirigida\n", pid_p);
    printf("Padre: Esperando a que P termine...\n");
    
    int status;
    waitpid(pid_p, &status, 0);
    
    printf("Padre: Proceso P terminó\n");
    printf("Padre: Verificando contenido del archivo output.txt:\n");
    
    // Mostrar el contenido del archivo generado
    system("echo '--- Contenido de output.txt ---'");
    system("cat output.txt");
    system("echo '--- Fin del archivo ---'");
    
    printf("Padre: Finalizando\n");
    return 0;
}