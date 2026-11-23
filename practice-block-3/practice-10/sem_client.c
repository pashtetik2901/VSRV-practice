/* Последний листинг: клиент ждёт готовую строку от сервера. */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 4321
#define SEM_KEY 9876
#define SHM_SIZE 256

int main(void)
{
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0600);
    int semid = semget(SEM_KEY, 1, 0600);
    char *memory = shmat(shmid, NULL, 0);

    printf("Waiting for server data...\n");
    fflush(stdout);

    struct sembuf wait_ready = {0, -1, 0};
    semop(semid, &wait_ready, 1);

    printf("Received: %s\n", memory);

    shmdt(memory);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}
