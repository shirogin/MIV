#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "Dijkstra.h"
//#include <sys/msg.h>
//#include <sys/shm.h>

#define Seprate printf("\n\n ----------------------------------------------------------- \n\n")

#define CLE1 1
#define CLE2 2
#define CLE3 3

#define N 20
#define M 5

void ProdF(ProdS, ConsProdS) int ProdS, ConsProdS;
{
    for (int i = 1; i <= N; i++)
    {
        printf("    Process Prod : Genrate %d and sent it in a message\n", i);
        V(ConsProdS);
        P(ProdS);
    }
    exit(0);
}
void ConsProdF(ProdS, ConsProdS, ConsS) int ProdS, ConsProdS, ConsS;
{
    for (int i = 1; i <= N; i++)
    {
        P(ConsProdS);
        printf("    Process ConsProd : Message %d Recieved.\n\n", i);
        V(ProdS);
    }
    Seprate;
    for (int i = 0; i < M; i++)
    {
        printf("    Process ConsProd : Stamp %d has been sent\n", i);
        V(ConsS);
        P(ConsProdS);
    }
    exit(0);
}
void ConsF(ConsProdS, ConsS) int ConsProdS, ConsS;
{
    for (int i = 0; i < M; i++)
    {
        P(ConsS);
        printf("    Process ConsF : Stamp %d has been recieved.\n\n", i);
        V(ConsProdS);
    }
    exit(0);
}

int main()
{
    int ProdS = sem_create(CLE1, 0),
        ConsProdS = sem_create(CLE2, 0),
        ConsS = sem_create(CLE3, 0);
    Seprate;
    printf("    Creating Semaphores: ProdS : %d | ConsProdS : %d | ConsS : %d", ProdS, ConsProdS, ConsS);
    Seprate;
    pid_t ProdPID, ConsProdPID, ConsPID;

    ProdPID = fork();
    if (ProdPID == 0)
        ProdF(ProdS, ConsProdS);

    ConsProdPID = fork();
    if (ConsProdPID == 0)
        ConsProdF(ProdS, ConsProdS, ConsS);

    ConsPID = fork();
    if (ConsPID == 0)
        ConsF(ConsProdS, ConsS);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    Seprate;
    printf("    Deleting Semaphores");
    sem_delete(ProdS);
    sem_delete(ConsProdS);
    sem_delete(ConsS);
    Seprate;
    return 0;
}