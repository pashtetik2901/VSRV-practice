#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]){
    int fd[2];
    pipe(fd);

    if (fork() != 0){
        close(fd[READ]);
        dup2(fd[WRITE], fileno(stdout));
        close(fd[WRITE]);

        execlp(argv[1], argv[1], (char *) NULL);
        perror("connect");
    } else {
        close(fd[WRITE]);
        dup2(fd[READ], fileno(stdin));
        close(fd[READ]);

        execlp(argv[2], argv[2], (char *) NULL);
        perror("connect");
    }
}