#include <sys/shm.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <string.h>
typedef struct shmid_ds sh_Buffer;
#define PathSHM "SHM.h"
void printSHM(int shmid, int pKey)
{
    printf("\n\tIdentificateur du segment: %d \n", shmid);
    printf("    Ce segment est associe a la cle unique: %d\n\n", pKey);
}
int shm_get(cle) const int cle;
{
    int shmid, /* identificateur de la memoire commune */
        pKey = ftok(PathSHM, (key_t)cle);
    if (pKey == -1)
    {
        perror("impossible de créer une cle");
        exit(1);
    }
    shmid = shmget((pKey), 0, SHM_R | SHM_W);
    if (shmid == -1)
    {
        perror("Échec lors de l'obtention de la mémoire partagée");
        exit(1);
    }
    printSHM(shmid, pKey);
    return (shmid);
}
int shm_create(const int cle, const int size)
{
    int shmid, /* identificateur de la memoire commune */
        pKey = ftok(PathSHM, (key_t)cle);
    if (pKey == -1)
    {
        perror("impossible de créer une cle");
        exit(1);
    }
    shmid = shmget((pKey), size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
    if (shmid == -1)
    {
        perror("Echec pendant la creation de memoire partagee");
        shmid = shm_get(cle);
    }
    else
        printSHM(shmid, pKey);

    return (shmid);
}

void shm_delete(const int shmid)
{
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        perror("Erreur shmctl()");
        exit(1);
    }
}

char *shm_read(const int shmid)
{
    char *mem, *cpy = NULL;
    if ((mem = shmat(shmid, 0, 0)) == (char *)-1)
        perror("Attachement impossible pendant la lecture");
    else
    {
        cpy = strdup(mem);
        if (shmdt(mem) == -1)
            perror("Détachement impossible pendant la lecture");
    }
    return cpy;
}

int shm_readInt(const int shmid)
{
    char *r = shm_read(shmid);
    if (r == NULL)
        return -1;
    return atoi(r);
}
void shm_change(const int shmid, const char *tochange)
{
    char *mem;
    if ((mem = shmat(shmid, 0, 0)) == (char *)-1)
    {
        perror("Attachement impossible en changemant");
    }
    else
    {
        strcpy(mem, tochange);
        printf("Mémoire partagée remplacée par : %s\n", mem);
        if (shmdt(mem) == -1)
            perror("Détachement impossible pendant la lecture");
    }
}
void shm_changeInt(const int shmid, const int tochange)
{
    char tochangeS[12];
    sprintf(tochangeS, "%d", tochange);
    shm_change(shmid, strdup(tochangeS));
}
int shm_createV(const int cle, const int size, const int initial)
{
    int shmid = shm_create(cle, size);
    shm_changeInt(shmid, initial);
    return shmid;
}
void shm_State(const int shmid)
{
    sh_Buffer buf;
    if (shmctl(shmid, IPC_STAT, &buf) == -1)
    {
        perror("Erreur shmctl()");
        exit(1);
    }
    else
    {
        printf(" ------------------------------------------------------------ \n");
        printf("|   ETAT DU SEGMENT DE MEMOIRE PARTAGEE %.9d            |\n", shmid);
        printf("|   Identificateur de l'utilisateur proprietaire: %.9d  |\n", buf.shm_perm.uid);
        printf("|   Identificateur du groupe proprietaire: %.9d         |\n", buf.shm_perm.gid);
        printf("|   Identificateur de l'utilisateur createur: %.9d      |\n", buf.shm_perm.cuid);
        printf("|   Identificateur du groupe createur: %.9d             |\n", buf.shm_perm.cgid);
        printf("|   Mode d'acces: %.9d                                  |\n", buf.shm_perm.mode);
        printf("|   Taille de la zone memoire: %.9ld                     |\n", buf.shm_segsz);
        printf("|   Pid du createur: %.9d                               |\n", buf.shm_cpid);
        printf("|   Pid (derniere operation): %.9d                      |\n", buf.shm_lpid);
        printf(" ------------------------------------------------------------\n");
    }
}