#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "SHM.h"

#define CLE 123

int main()
{
    int shmid; /* identificateur de la memoire commune */
    int size = 12;
    shmid = shm_create(CLE, size);
    shm_State(shmid);
    shm_changeInt(shmid, 54);
    if (fork() == 0)
    {
        printf("memory is : %d\n", shm_readInt(shmid));
        exit(1);
    }
    wait(NULL);
    //shm_delete(shmid);
    return 0;
}