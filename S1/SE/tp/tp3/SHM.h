#include <sys/shm.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <string.h>
typedef struct shmid_ds sh_Buffer;
#define PathSHM "SHM.h"

int shm_create(const int cle, const int size)
{
    int shmid, /* identificateur de la memoire commune */
        pKey = ftok(PathSHM, (key_t)cle);
    if (pKey == -1)
    {
        perror("impossible de créer une cle");
        exit(1);
    }
    shmid = shmget((pKey), size, IPC_CREAT | SHM_R | SHM_W);
    if (shmid == -1)
        perror("Echec pendant la creation de memoire partagee");
    else
    {
        printf("\n\tIdentificateur du segment: %d \n", shmid);
        printf("    Ce segment est associe a la cle unique: %d\n\n", pKey);
    }

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
char *shm_attatch(const int shmid)
{
    char *mem = NULL;
    if ((mem = shmat(shmid, 0, 0)) == (char *)-1)
    {
        perror("Attachement impossible en changemant");
    }
    return mem;
}
void shm_dettatch(const char *mem)
{
    if (shmdt(mem) == -1)
        perror("Détachement impossible");
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