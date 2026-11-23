#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1

char *message = "Hello from parent!";

int main(){
    int fd[2], bytesRead;
    char buffer[128];

    pipe(fd);

    if(fork() == 0){
        close(fd[READ]);
        write(fd[WRITE], message, strlen(message) + 1);
        close(fd[WRITE]);
    } else {
        close(fd[WRITE]);
        bytesRead = read(fd[READ], buffer, sizeof(buffer));
        close(fd[READ]);

        printf("Read String: %s\nBytesRead = %d\n", buffer, bytesRead);
    }

    return 0;
}