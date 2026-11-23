/* Листинг 13.4: сервер записывает строку и разрешает её прочитать. */
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 4321
#define SEM_KEY 9876
#define SHM_SIZE 256

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;

int main(void)
{
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0600);
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
    char *memory = shmat(shmid, NULL, 0);

    union semun arg;
    arg.val = 0;
    semctl(semid, 0, SETVAL, arg);

    char line[128] = {0};
    printf("Server ready. Enter a string:\n");
    fflush(stdout);
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';

    strcpy(memory, line);
    printf("Written: %s\n", memory);

    struct sembuf signal_ready = {0, 1, 0};
    semop(semid, &signal_ready, 1);

    shmdt(memory);
    return 0;
}
