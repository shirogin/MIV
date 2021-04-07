#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "Dijkstra.h"
#include "SHM.h"
#include "MSGS.h"
// printing
#define Seprate printf("\n\n ----------------------------------------------------------- \n\n")
#define Tab printf("    ")
// printing

// SymaphoreCles
#define ProdC 1
#define ConsProdC 2
#define ConsC 3
// SymaphoreCles

// MemoirePartageeCles
#define SHM_T_Cle 200
// MemoirePartageeCles

// MessagesCles
#define MSG_FileMess_Cle 100
// MessagesCles

// PreDefinition
#define N 20
#define M 5
// PreDefinition

// DefinitionDesProcessus
void ProdF(const int FileMess, const int ProdS)
{
    int i = 1;
    char temp[12];
    while (i <= N)
    {
        printf("    Processus Prod : Genrate %d and \n\n", i);
        sprintf(temp, "%d", i);
        msg_send(FileMess, N, temp);
        //sleep(1);
        i++;
    }
    exit(0);
}
void ConsProdF(const int FileMess, const int T, const int ProdS, const int ConsProdS, const int ConsS)
{
    int i = 1, j = 1;
    char *temp;
    int *tab = (int *)shm_attatch(T);
    while (i <= N)
    {
        temp = msg_recieve(FileMess, N);
        printf("    Processus ConsProd : %s\n\n", temp);
        P(ConsProdS);
        tab[(i - 1) % M] = i;
        V(ConsS);
        i++;
    }
    shm_dettatch((char *)tab);
    exit(0);
}
void ConsF(const int T, const int ConsProdS, const int ConsS)
{
    int i = 1;
    int *tab = (int *)shm_attatch(T);
    char *temp;
    while (i <= N)
    {
        P(ConsS);
        printf("    Processus ConsF :    Message afficher '%d'\n\n", tab[(i - 1) % M]);
        i++;
        sleep(5);
        V(ConsProdS);
    }
    shm_dettatch((char *)tab);
    exit(0);
}
// DefinitionDesProcessus
int main()
{
    // Creation

    // CreationDesSemaphores
    Seprate;
    int ProdS = sem_create(ProdC, 0),
        ConsProdS = sem_create(ConsProdC, M - 1),
        ConsS = sem_create(ConsC, 0);
    printf("    Création des sémaphores : ProdS : %d | ConsProdS : %d | ConsS : %d\n", ProdS, ConsProdS, ConsS);
    // CreationDesSemaphores

    // CreationDesMemoirePartagee
    Seprate;
    printf("Création des Mémoire Partagée : \n");
    int T = shm_create(SHM_T_Cle, 40 * M);
    printf("\t  Memoire partagée pour controle de T : %d\n", T);
    // CreationDesMemoirePartagee

    // CreationDeLaFilesDesMessage
    Seprate;
    int FileMess = msg_create(MSG_FileMess_Cle);
    printf("    Création des files des messages :  FileMess: %d \n", FileMess);
    Seprate;
    // CreationDesFilesDesMessage

    // Creation

    // CreationDesProcessus

    // ProcessusProd
    pid_t ProdPID = fork();
    if (ProdPID == 0)
        ProdF(FileMess, ProdS);
    // ProcessusProd

    // ProcessusConsProd
    pid_t ConsProdPID = fork();
    if (ConsProdPID == 0)
        ConsProdF(FileMess, T, ProdS, ConsProdS, ConsS);
    // ProcessusConsProd

    // ProcessusCons
    pid_t ConsPID = fork();
    if (ConsPID == 0)
        ConsF(T, ConsProdS, ConsS);
    // ProcessusCons

    // CreationDesProcessus

    // WaitProcessus
    wait(NULL);
    wait(NULL);
    wait(NULL);
    // WaitProcessus

    // Appuyez
    Seprate;
    printf("    Appuyez sur n'importe quelle touche pour supprimer les IPCS : ");
    int c = getchar();
    // Appuyez

    // Suppression

    // SuppressionFilesDesMessage
    Seprate;
    printf("    Suppression de la file d'attente de messages");
    msg_delete(FileMess);
    // SuppressionFilesDesMessage

    // SuppressionMémoirePartagée
    Seprate;
    printf("    Suppression de la mémoire partagée");
    shm_delete(T);
    // SuppressionMémoirePartagée

    // SuppressionDesSemaphores
    Seprate;
    printf("    Suppression des sémaphores");
    sem_delete(ProdS);
    sem_delete(ConsProdS);
    sem_delete(ConsS);
    // SuppressionDesSemaphores

    Seprate;
    // Suppression
    return 0;
}