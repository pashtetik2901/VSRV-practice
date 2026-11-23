#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define WRITE 1
#define READ 0

int main(int argc, char *argv[]){
    int fd[2];
    pipe(fd);

    if( fork() == 0){
        close(fd[READ]);

        dup2(fd[WRITE], fileno(stdout));
        close(fd[WRITE]);

        execlp(argv[1], argv[1], (char *) NULL);
        exit(1);
    }

    if (fork() == 0){
        close(fd[WRITE]);

        dup2(fd[READ], fileno(stdin));
        close(fd[READ]);

        execlp("wc", "wc", "-l", (char *) NULL);
        exit(1);
    }

    close(fd[READ]);
    close(fd[WRITE]);

    wait(NULL);
    wait(NULL);

    return 0;
}
