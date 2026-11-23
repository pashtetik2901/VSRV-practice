#include <stdio.h>
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
    int id = shmget(SHM_KEY, sizeof(struct shmseg), 0600);
    struct shmseg *memory = shmat(id, NULL, 0);

    for (int i = 0; i < 5; i++) {
        sem_wait(&memory->ready);

        printf("Read %d bytes:\n%s\n", memory->cnt, memory->buf);

        sem_post(&memory->done);
    }

    shmdt(memory);

    return 0;
}
