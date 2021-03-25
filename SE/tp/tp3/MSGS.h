#include <sys/msg.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct msqid_ds msqid_ds;
#define MSG_SIZE_TEXT 256
typedef struct msgtext
{
    long mtype;                 /* type du message */
    char mtexte[MSG_SIZE_TEXT]; /* texte du message */
} msgtext;
#define PathMSG "MSGS.h"

#define MSG_R 0400
#define MSG_W 0200

#define MSG_TO_Buffer "message : %s"

void printMSG(msgid, pKey) int msgid, pKey;
{
    printf("\n    identificateur de la file: %d \n", msgid);
    printf("    cette file est identifiee par la cle unique : %d\n\n", pKey);
}
int msg_get(const int cle)
{
    int msgid,
        pKey = ftok(PathMSG, (key_t)cle);
    if (pKey == -1)
    {
        perror("impossible de créer une cle");
        exit(1);
    }
    msgid = msgget(pKey, MSG_R | MSG_W);
    if (msgid == -1)
    {
        perror("Échec lors de l'obtention de la file des messages");
        exit(1);
    }
    printMSG(msgid, pKey);
    return (msgid);
}
int msg_create(const int cle)
{
    int msgid, /* identificateur de la file des messages */
        pKey = ftok(PathMSG, (key_t)cle);
    if (pKey == -1)
    {
        perror("impossible de créer une cle");
        exit(1);
    }
    msgid = msgget((pKey), IPC_CREAT | IPC_EXCL | MSG_R | MSG_W);
    if (msgid == -1)
    {
        perror("Echec pendant la creation de la file des messages");
        msgid = msg_get(cle);
    }
    else
        printMSG(msgid, pKey);

    return (msgid);
}

void msg_delete(const int msgid)
{
    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        perror("Erreur lors de la suppression de la file des messages");
        exit(1);
    }
}
char *msg_recieve(const int msgid, const long mtype)
{
    msgtext buf;
    buf.mtype = mtype;
    int lg;
    if ((lg = msgrcv(msgid, &buf, MSG_SIZE_TEXT, mtype, IPC_NOWAIT | MSG_NOERROR)) == -1)
    {
        perror("Pas de message");
        return NULL;
    }
    char *message = (char *)malloc(sizeof(char) * lg);
    sscanf(buf.mtexte, MSG_TO_Buffer, message);
    printf("\"%s\" longeur %d de type %ld est recu depuis %d\n", buf.mtexte, lg, buf.mtype, msgid);
    return message;
}
void msg_send(const int msgid, const long mtype, const char *message)
{
    msgtext buf;
    buf.mtype = mtype;
    sprintf(buf.mtexte, MSG_TO_Buffer, message);
    if (msgsnd(msgid, &buf, strlen(buf.mtexte) + 1, IPC_NOWAIT) == -1)
    {
        perror("impossible d'envoyer le message");
        exit(-1);
    }
    else
        printf("%s de type %ld envoye a %d\n", buf.mtexte, buf.mtype, msgid);
}
void msg_State(const int msgid)
{
    msqid_ds buf;
    if (msgctl(msgid, IPC_STAT, &buf) == -1)
    {
        perror("Erreur lors de l'obtention des States de la file des messages");
        exit(1);
    }
    else
    {
        printf(" ------------------------------------------------------------ \n");
        printf("|   id de la file de messages %.9d                      |\n", msgid);
        printf("|   identificateur de l'utilisateur proprietaire: %.9d  |\n", buf.msg_perm.uid);
        printf("|   identificateur du groupe proprietaire: %.9d         |\n", buf.msg_perm.gid);
        printf("|   identificateur de l'utilisateur createur: %.9d      |\n", buf.msg_perm.cuid);
        printf("|   identificateur du groupe createur: %.9d             |\n", buf.msg_perm.cgid);
        printf("|   mode d'acces: %.9d                                  |\n", buf.msg_perm.mode);
        printf("|   nb courant d'octets dans la file : %.9ld             |\n", buf.msg_cbytes);
        printf("[   nb de messages dans la file: %.9ld                   |\n", buf.msg_qnum);
        printf("|   nb maximal d'octets de la file: %.9ld                |\n", buf.msg_qbytes);
        printf(" ------------------------------------------------------------\n");
    }
}