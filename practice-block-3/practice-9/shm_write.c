#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define SHM_KEY 0x1234
#define BUF_SIZE 1024

struct shmseg {
    sem_t ready;
    sem_t done;
    int cnt;
    char buf[BUF_SIZE];
} shmseg;

int main(void)
{
    int id = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | 0600);
    struct shmseg *memory = shmat(id, NULL, 0);

    sem_init(&memory->ready, 1, 0);
    sem_init(&memory->done, 1, 0);

    printf("Writer ready. Start shm_read.\n");
    fflush(stdout);

    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < 26; j++){
            memory->buf[j] = 'A' + j;
        }

        memory->buf[BUF_SIZE - 1] = '\0';
        memory->cnt = strlen(memory->buf);

        printf("Wrote %d bytes: %c\n", memory->cnt, 'A' + i);

        sem_post(&memory->ready);
        sem_wait(&memory->done);
    }

    sem_destroy(&memory->ready);
    sem_destroy(&memory->done);
    shmdt(memory);
    shmctl(id, IPC_RMID, NULL);

    return 0;
}
