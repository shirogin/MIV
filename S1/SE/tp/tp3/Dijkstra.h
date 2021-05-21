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

int sem_create(key_t cle, int initval)
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
    sempar.sem_flg = 0;
    if (semop(semid, &sempar, 1) == -1)
        perror("Erreur operation P");
}
void V(semid) int semid;
{
    struct sembuf sempar;
    sempar.sem_num = 0;
    sempar.sem_op = 1;
    sempar.sem_flg = 0;
    if (semop(semid, &sempar, 1) == -1)
        perror("Erreur operation V");
}

void sem_delete(int semid)
{
    if (semctl(semid, 0, IPC_RMID, 0) == -1)
        perror("Erreur dans destruction semaphore");
}
void sem_State(const int semid)
{
    struct semid_ds buf;
    if (semctl(semid, 0, IPC_STAT, &buf) == -1)
    {
        perror("Erreur semctl()");
        exit(1);
    }
    else
    {
        printf(" ------------------------------------------------------------ \n");
        printf("|   ETAT DU SEGMENT DE MEMOIRE PARTAGEE %.9d            |\n", semid);
        printf("|   Identificateur de l'utilisateur proprietaire: %.9d  |\n", buf.sem_perm.uid);
        printf("|   Identificateur du groupe proprietaire: %.9d         |\n", buf.sem_perm.gid);
        printf("|   Identificateur de l'utilisateur createur: %.9d      |\n", buf.sem_perm.cuid);
        printf("|   Identificateur du groupe createur: %.9d             |\n", buf.sem_perm.cgid);
        printf("|   Mode d'acces: %.9d                                  |\n", buf.sem_perm.mode);
        printf("|   number of semaphores in set: %.9ld                     |\n", buf.sem_nsems);
        printf(" ------------------------------------------------------------\n");
    }
}