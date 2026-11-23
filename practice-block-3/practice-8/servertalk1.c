#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO_FILE "MYFIFO"

int main(void)
{
    int fd;
    int bytesRead;
    char buffer[128];

    mkfifo(FIFO_FILE, 0600);
    fd = open(FIFO_FILE, O_RDONLY);

    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);

        if (strcmp(buffer, "end\n") == 0) {
            break;
        }
    }

    close(fd);
    unlink(FIFO_FILE);

    return 0;
}