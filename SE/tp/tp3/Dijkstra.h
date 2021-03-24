#include <sys/sem.h>
#include <sys/errno.h>



/*
*   Implementation des semaphores de Dijkstra a l'aide des semaphores de SystemV.
*   sem_create(): creation d'un semaphore
*   P() : realisation de l'operation P sur un semaphore
*   V() : realisation de l'operation V sur un semaphore
*   sem_delete() : suppression d'un semaphore
*
*/

int sem_create(cle, initval)
/* creation d'un semaphore relie a cle */
/* de valeur initiale initval
*/
key_t cle ;
int initval ;
{
    int semid;
    union semun
    {
        int val;
        struct semid_ds *buf;
        ushort *array;
    } arg_ctl;
    semid = semget(ftok("Dijkstra.h", cle), 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1)
    {
        semid = semget(ftok("Dijkstra.h", cle), 1, 0666);
        if (semid == -1)
        {
            perror("Erreur semget()");
            exit(1);
        }
    }
    arg_ctl.val = initval;
    if (semctl(semid, 0, SETVAL, arg_ctl) == -1)
    {
        perror("Erreur initialisation semaphore");
        exit(1);
    }
    return (semid);
}
void P(semid) int semid;
{
    struct sembuf sempar;
    sempar.sem_num = 0;
    sempar.sem_op = -1;
    sempar.sem_flg = SEM_UNDO;
    if (semop(semid, &sempar, 1) == -1)
        perror("Erreur operation P");
}
void V(semid) int semid;
{
    struct sembuf sempar;
    sempar.sem_num = 0;
    sempar.sem_op = 1;
    sempar.sem_flg = SEM_UNDO;
    if (semop(semid, &sempar, 1) == -1)
        perror("Erreur operation V");
}
void sem_delete(semid) int semid;
{
    if (semctl(semid, 0, IPC_RMID, 0) == -1)
        perror("Erreur dans destruction semaphore");
}