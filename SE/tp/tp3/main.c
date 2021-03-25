#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "Dijkstra.h"
#include "SHM.h"
#include "MSGS.h"
#pragma region printing
#define Seprate printf("\n\n ----------------------------------------------------------- \n\n")
#define Tab printf("    ")
#pragma endregion printing

#pragma region SymaphoreCles
#define ProdC 1
#define ConsProdC 2
#define ConsC 3
#pragma endregion SymaphoreCles

#pragma region MemoirePartageeCles
#define SHM_Cle_iN 10
#define SHM_Cle_iM 20
#pragma endregion MemoirePartageeCles

#pragma region MessagesCles
#define MSG_FileMess_Cle 100
#define MSG_T_Cle 200
#pragma endregion MessagesCles

#pragma region PreDefinition
#define N 20
#define M 5
#pragma endregion PreDefinition

#pragma region DefinitionDesProcessus
void ProdF(const int iN_SM, const int FileMess, const int ProdS, const int ConsProdS)
{
    int i = shm_readInt(iN_SM);
    char temp[30];
    while (i <= N)
    {
        sprintf(temp, "%d", i);
        printf("    Processus Prod : Genrate %d and ", i);
        msg_send(FileMess, i, temp);
        V(ConsProdS);
        P(ProdS);
        i = shm_readInt(iN_SM);
    }
    exit(0);
}
void ConsProdF(const int iN_SM, const int iM_SM, const int FileMess, const int T, const int ProdS, const int ConsProdS, const int ConsS)
{
    int i = shm_readInt(iN_SM);
    char *temp;
    while (i <= N)
    {
        P(ConsProdS);
        printf("    Processus ConsProd : ");
        temp = msg_recieve(FileMess, i);
        i++;
        Tab;
        shm_changeInt(iN_SM, i);
        V(ProdS);
    }
    Seprate;
    i = shm_readInt(iM_SM);
    char temp2[100];
    while (i <= M)
    {
        printf("    Processus ConsProd : ");
        int x = (i - 1) * 4;
        sprintf(temp2, "Messages [%d %d %d %d]", x + 1, x + 2, x + 3, x + 4);
        msg_send(T, i, temp2);
        V(ConsS);
        P(ConsProdS);
        i = shm_readInt(iM_SM);
    }
    exit(0);
}
void ConsF(const int iM_SM, const int T, const int ConsProdS, const int ConsS)
{
    int i = shm_readInt(iM_SM);
    char *temp;
    while (i <= M)
    {
        P(ConsS);
        printf("    Processus ConsF : ");
        temp = msg_recieve(T, i);
        i++;
        Tab;
        shm_changeInt(iM_SM, i);
        V(ConsProdS);
    }
    exit(0);
}
#pragma endregion DefinitionDesProcessus
int main()
{
#pragma region Creation

#pragma region CreationDesSemaphores
    Seprate;
    int ProdS = sem_create(ProdC, 0),
        ConsProdS = sem_create(ConsProdC, 0),
        ConsS = sem_create(ConsC, 0);
    printf("    Création des sémaphores : ProdS : %d | ConsProdS : %d | ConsS : %d\n", ProdS, ConsProdS, ConsS);
#pragma endregion CreationDesSemaphores

#pragma region CreationDesMemoirePartagee
    Seprate;
    int iN_SM = shm_createV(SHM_Cle_iN, 12, 1),
        iM_SM = shm_createV(SHM_Cle_iM, 12, 1);
    printf("    Création des Mémoire Partagée : \n      Memoire partagée pour controle de N : %d \n      Memoire partagée pour controle de M : %d\n", iN_SM, iM_SM);
#pragma endregion CreationDesMemoirePartagee

#pragma region CreationDesFilesDesMessage
    Seprate;
    int FileMess = msg_create(MSG_FileMess_Cle),
        T = msg_create(MSG_T_Cle);
    printf("    Création des files des messages :  FileMess: %d | T : %d\n", FileMess, T);
    Seprate;
#pragma endregion CreationDesFilesDesMessage

#pragma endregion Creation

#pragma region CreationDesProcessus

#pragma region ProcessusProd
    pid_t ProdPID = fork();
    if (ProdPID == 0)
        ProdF(iN_SM, FileMess, ProdS, ConsProdS);
#pragma endregion ProcessusProd

#pragma region ProcessusConsProd
    pid_t ConsProdPID = fork();
    if (ConsProdPID == 0)
        ConsProdF(iN_SM, iM_SM, FileMess, T, ProdS, ConsProdS, ConsS);
#pragma endregion ProcessusConsProd

#pragma region ProcessusCons
    pid_t ConsPID = fork();
    if (ConsPID == 0)
        ConsF(iM_SM, T, ConsProdS, ConsS);
#pragma endregion ProcessusCons

#pragma endregion CreationDesProcessus

#pragma region WaitProcessus
    wait(NULL);
    wait(NULL);
    wait(NULL);
#pragma endregion WaitProcessus

#pragma region Appuyez
    Seprate;
    printf("    Appuyez sur n'importe quelle touche pour supprimer les IPCS : ");
    int c = getchar();
#pragma endregion Appuyez

#pragma region Suppression

#pragma region SuppressionFilesDesMessage
    Seprate;
    printf("    Suppression de la file d'attente de messages");
    msg_delete(FileMess);
    msg_delete(T);
#pragma endregion SuppressionFilesDesMessage

#pragma region SuppressionMémoirePartagée
    Seprate;
    printf("    Suppression de la mémoire partagée");
    shm_delete(iN_SM);
    shm_delete(iM_SM);
#pragma endregion SuppressionMémoirePartagée

#pragma region SuppressionDesSemaphores
    Seprate;
    printf("    Suppression des sémaphores");
    sem_delete(ProdS);
    sem_delete(ConsProdS);
    sem_delete(ConsS);
#pragma endregion SuppressionDesSemaphores

    Seprate;
#pragma endregion Suppression
    return 0;
}