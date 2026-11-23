#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define REQUEST "fifo_request"
#define RESPONSE "fifo_response"

void reverse_string(char *str)
{
    int first = 0;
    int last = strlen(str) - 1;
    char temp;

    while (first < last) {
        temp = str[first];
        str[first] = str[last];
        str[last] = temp;

        first++;
        last--;
    }
}

int main(void)
{
    int fdRead;
    int fdWrite;
    int bytesRead;
    char buffer[128];

    mkfifo(REQUEST, 0600);
    mkfifo(RESPONSE, 0600);

    fdRead = open(REQUEST, O_RDONLY);
    fdWrite = open(RESPONSE, O_WRONLY);

    while ((bytesRead = read(fdRead, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';

        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "end") == 0) {
            break;
        }

        reverse_string(buffer);

        write(fdWrite, buffer, strlen(buffer) + 1);
        printf("Sent: %s\n", buffer);
    }

    close(fdRead);
    close(fdWrite);

    unlink(REQUEST);
    unlink(RESPONSE);

    return 0;
}