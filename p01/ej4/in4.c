#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
    pid_t pid_c;
    printf("Padre (PID: %d) iniciando...\n", getpid());

    pid_c = fork();
    if(pid_c == -1) {
        perror("Error en fork para c");
        exit(EXIT_FAILURE);
    }

    if(pid_c == 0){
        printf("Hijo C (PID: %d) ejecutando...\n", getpid());

        close(STDIN_FILENO);

        int fd = open("output.txt", O_RDONLY, 777);//reuso el output.txt que genera in3 pero ahora como input
        if(fd == -1) {
            perror("Error abriendo archivo output.txt");
            exit(EXIT_FAILURE);
        }

        execve("./c", (char*[]){"./c", NULL}, NULL);
        perror("Error ejecutando c");
        exit(EXIT_FAILURE);
    }

    waitpid(pid_c, NULL, 0);
    return 0;
}