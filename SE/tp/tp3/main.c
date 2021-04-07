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
#define ConsProdC 2
#define ConsC 3
// SymaphoreCles

// MemoirePartageeCles
#define SHM_T_Cle 20
// MemoirePartageeCles

// MessagesCles
#define MSG_FileMess_Cle 100
// MessagesCles

// PreDefinition
#define N 20
#define M 5
// PreDefinition

// DefinitionDesProcessus
void ProdF(const int FileMess)
{
    int i = 1;
    char temp[12];
    while (i <= N)
    {
        sprintf(temp, "message %d", i);
        msg_send(FileMess, N, temp);
        printf("    Processus Prod : Genrer %d & l'envoye  \n\n", i);
        //sleep(1);
        i++;
    }
    exit(0);
}
void ConsProdF(const int FileMess, const int T, const int ConsProdS, const int ConsS)
{
    int i = 1, j = 1;
    char *temp;
    int *tab = (int *)shm_attatch(T);
    while (i <= N)
    {
        temp = msg_recieve(FileMess, N);
        printf("    Processus ConsProd : Message est recu '%s'\n\n", temp);
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
        //sleep(2);
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
    int ConsProdS = sem_create(ConsProdC, M - 1),
        ConsS = sem_create(ConsC, 0);
    printf("    Création des sémaphores :  ConsProdS : %d | ConsS : %d\n", ConsProdS, ConsS);
    // CreationDesSemaphores

    // CreationDesMemoirePartagee
    Seprate;
    printf("Création des Mémoire Partagée : \n");
    int T = shm_create(SHM_T_Cle, sizeof(int) * M);
    printf("\t  Memoire partagée pour controle de T : %d\n", T);
    // CreationDesMemoirePartagee

    // CreationDeLaFilesDesMessage
    Seprate;
    int FileMess = msg_create(MSG_FileMess_Cle);
    printf("    Création la file des messages :  FileMess: %d \n", FileMess);
    Seprate;
    // CreationDesFilesDesMessage

    // Creation

    // CreationDesProcessus

    // ProcessusProd
    pid_t ProdPID = fork();
    if (ProdPID == 0)
        ProdF(FileMess);
    // ProcessusProd

    // ProcessusConsProd
    pid_t ConsProdPID = fork();
    if (ConsProdPID == 0)
        ConsProdF(FileMess, T, ConsProdS, ConsS);
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
    sem_delete(ConsProdS);
    sem_delete(ConsS);
    // SuppressionDesSemaphores

    Seprate;
    // Suppression
    return 0;
}