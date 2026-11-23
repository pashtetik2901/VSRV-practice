/* Листинг 13.3: семафор защищает всю работу с общим счётчиком. */
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SHM_KEY 0x12345
#define TOTAL_COUNT 10000

struct shmseg {
    volatile int cntr;
} shmseg;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;

void increment(struct shmseg *memory, int semid)
{
    struct sembuf lock = {0, -1, 0};
    struct sembuf unlock = {0, 1, 0};

    semop(semid, &lock, 1);

    int value = memory->cntr;
    sleep(1);

    for (int i = 0; i < TOTAL_COUNT; i++) {
        value++;
        memory->cntr = value;
    }

    semop(semid, &unlock, 1);
}

int main(void)
{
    int id = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | 0600);
    struct shmseg *memory = shmat(id, NULL, 0);
    memory->cntr = 0;

    int semid = semget(IPC_PRIVATE, 1, 0600);
    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    if (fork() == 0) {
        increment(memory, semid);
        shmdt(memory);
        return 0;
    }

    increment(memory, semid);
    wait(NULL);

    printf("Expected: %d\n", 2 * TOTAL_COUNT);
    printf("With semaphore: %d\n", memory->cntr);

    semctl(semid, 0, IPC_RMID);
    shmdt(memory);

    return 0;
}
