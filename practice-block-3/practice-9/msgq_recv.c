#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[200];
} message;

int main(void)
{
    key_t key = ftok("msgq.txt", 'B');
    int id = msgget(key, 0600);

    struct message msg;

    while (1) {
        msgrcv(id, &msg, sizeof(msg.mtext), 1, 0);
        printf("Received: %s\n", msg.mtext);

        if (strcmp(msg.mtext, "end") == 0) {
            break;
        }
    }

    msgctl(id, IPC_RMID, NULL);
    remove("msgq.txt");

    return 0;
}
