#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(void)
{
    const char *fifo = "/tmp/my_fifo";

    mkfifo(fifo, 0600);

    if (fork() == 0) {
        int fd = open(fifo, O_RDONLY);
        char buffer[128];

        read(fd, buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(fd);
    } else {
        int fd = open(fifo, O_WRONLY);
        const char *message = "Hello from parent!";

        write(fd, message, strlen(message) + 1);

        close(fd);
        wait(NULL);

        unlink(fifo);
    }

    return 0;
}