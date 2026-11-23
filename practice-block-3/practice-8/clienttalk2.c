#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define REQUEST "fifo_request"
#define RESPONSE "fifo_response"

int main(void)
{
    int fdWrite;
    int fdRead;
    char buffer[128];

    fdWrite = open(REQUEST, O_WRONLY);
    fdRead = open(RESPONSE, O_RDONLY);

    printf("Enter messages. To finish, enter end.\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        write(fdWrite, buffer, strlen(buffer) + 1);

        if (strcmp(buffer, "end") == 0) {
            break;
        }

        read(fdRead, buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);
    }

    close(fdWrite);
    close(fdRead);

    return 0;
}