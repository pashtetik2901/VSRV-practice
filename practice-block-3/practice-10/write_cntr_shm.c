/* Листинг 13.1: намеренно НЕПРАВИЛЬНЫЙ совместный доступ без семафора. */
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_KEY 0x12345
#define TOTAL_COUNT 10000

struct shmseg {
    volatile int cntr;
} shmseg;

void increment(struct shmseg *memory)
{
    int value = memory->cntr;

    sleep(1);

    for (int i = 0; i < TOTAL_COUNT; i++) {
        value++;
        memory->cntr = value;
    }
}

int main(void)
{
    int id = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | 0600);
    struct shmseg *memory = shmat(id, NULL, 0);
    memory->cntr = 0;

    if (fork() == 0) {
        increment(memory);
        shmdt(memory);
        return 0;
    }

    increment(memory);
    wait(NULL);

    printf("Expected: %d\n", 2 * TOTAL_COUNT);
    printf("Without semaphore: %d\n", memory->cntr);

    shmdt(memory);
 
    return 0;
}
