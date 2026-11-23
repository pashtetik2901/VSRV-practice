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
    FILE *file = fopen("msgq.txt", "a");
    fclose(file);

    key_t key = ftok("msgq.txt", 'B');
    int id = msgget(key, IPC_CREAT | 0600);

    struct message msg;
    msg.mtype = 1;

    printf("Queue ready. Enter messages; Ctrl+D to finish.\n");

    while (fgets(msg.mtext, sizeof(msg.mtext), stdin) != NULL) {
        msg.mtext[strcspn(msg.mtext, "\n")] = '\0';
        msgsnd(id, &msg, strlen(msg.mtext) + 1, 0);
    }

    strcpy(msg.mtext, "end");
    msgsnd(id, &msg, strlen(msg.mtext) + 1, 0);

    return 0;
}
