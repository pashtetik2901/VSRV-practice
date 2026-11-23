#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void)
{
    const char *name = "/pr9_shared_memory";
    int size = 4096;

    int fd = shm_open(name, O_CREAT | O_RDWR, 0600);
    ftruncate(fd, size);

    char *memory = mmap(NULL, size, PROT_READ | PROT_WRITE,
                        MAP_SHARED, fd, 0);
                        
    strcpy(memory, "Hello from parent!");

    if (fork() == 0) {
        printf("Child read: %s\n", memory);
    } else {
        wait(NULL);
        shm_unlink(name);
    }

    munmap(memory, size);
    close(fd);

    return 0;
}
