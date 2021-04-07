#include "MSGS.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#define CLE 123
int main()
{
    int msqid = msg_create(CLE);
    msg_State(msqid);
    msg_send(msqid, 1, "Youcef was here");
    msg_send(msqid, 1, "Larbi wasn't here");
    if (fork() == 0)
    {
        exit(1);
        printf("\n");
        char *temp = msg_recieve(msqid, 1);
        if (temp != NULL)
            printf("Message recieved is : %s\n", temp);
        temp = msg_recieve(msqid, 1);
        if (temp != NULL)
            printf("Message recieved is : %s\n", temp);
        temp = msg_recieve(msqid, 2);
        if (temp != NULL)
            printf("Message recieved is : %s\n", temp);
        exit(1);
    }
    wait(NULL);
    //msg_delete(msqid);
    return 0;
}