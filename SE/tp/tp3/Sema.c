#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Dijkstra.h"

#define CLE 1
int main()
{
    int sem;
    sem = sem_create(CLE, 0);
    printf("Creation du semaphore d'identificateur %d\n", sem);
    if (fork() == 0)
    {
        printf("Je suis le fils et j'attends 5 secondes...\n");
        //sleep(5);
        printf("Je suis le fils et je fais V sur le semaphore\n");
        V(sem);
        //sleep(1);
        V(sem);
        V(sem);
        V(sem);
        exit(0);
    }
    else
    {
        printf("Je suis le pere et je me bloque en faisant P sur le semaphore\n\n");
        P(sem);
        P(sem);
        P(sem);
        P(sem);
        printf("Je suis le pere et je suis libre\n\n");
        sem_delete(sem);
    }
    return 0;
}