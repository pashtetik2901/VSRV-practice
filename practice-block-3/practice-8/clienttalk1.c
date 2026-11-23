#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"

int main(void)
{
    int fd;
    char buffer[128];

    fd = open(FIFO_FILE, O_WRONLY);

    printf("Enter messages. To finish, enter end.\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        write(fd, buffer, strlen(buffer));

        if (strcmp(buffer, "end\n") == 0) {
            break;
        }
    }

    close(fd);

    return 0;
}