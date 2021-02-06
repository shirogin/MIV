//debut fin PO
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <pthread.h> 

int TAB[] = {1, 12, 7,  57, 2, 10, 54, 47, 0, 16};

void printTable(int Tab[], int d,int f)
{
    printf("[ ");
    for (int i = d; i < f; i++)
        printf("%d, ", Tab[i]);
    printf("%d ]\n", Tab[f]);
}

void swap(int *a, int *b)
{
    int perm = *a;
    *a = *b;
    *b = perm;
}
void Copy(int original[],int copy[],int n){
    for (int i = 0; i < n; i++) copy[i]=original[i];
}
void Quick(int TAB[], int d, int f, int n)
{
    int pivot = (f + d) / 2, value = TAB[pivot], i = d, j = f;
    while (i != j)
    {
        while (TAB[i] < value) i++;
        while (TAB[j] > value) j--;
        swap(&TAB[j], &TAB[i]);
    }
    printf("debut : %d --- fin : %d --- INDEX_PIVOT : %d --- VALEUR_PIVOT : %d TABLE : ", d, f, pivot, value);
    printTable(TAB, d,f);
    if (i > (d + 1))
        Quick(TAB, d, i - 1, n);
    if (i < (f - 1))
        Quick(TAB, i + 1, f, n);
}
void AsyncFQuick(int *TAB[], int d, int f, int n,char *pos)
{
    int pivot = (f + d) / 2, value = (*TAB)[pivot], i = d, j = f;
    while (i != j)
    {
        while ((*TAB)[i] < value) i++;
        while ((*TAB)[j] > value) j--;
        swap(&(*TAB)[j], &(*TAB)[i]);
    }
    printf("Async %s debut : %d --- fin : %d --- INDEX_PIVOT : %d --- VALEUR_PIVOT : %d TABLE : ",pos, d, f, pivot, value);
    printTable((*TAB), d,f);
    
    
    if (i > (d + 1) && (fork()==0)){
        AsyncFQuick(TAB, d, i - 1, n,"left\0");
        exit(0);
	}
    if (i < (f - 1) && (fork()==0)){
        AsyncFQuick(TAB, i + 1, f, n,"right\0");
        exit(0);
	}

    wait(NULL);
	wait(NULL);
}
void AsyncTQuick( int d, int f, int n);
void *ThreadHandle(void *args){
    int *var=(int *) args;
    AsyncTQuick(var[0],var[1],var[2]);
    return NULL;
}
void AsyncTQuick(int d, int f, int n)
{
    int pivot = (f + d) / 2, value = TAB[pivot], i = d, j = f;
    while (i != j)
    {
        while (TAB[i] < value) i++;
        while (TAB[j] > value) j--;
        swap(&TAB[j], &TAB[i]);
    }
    printf("debut : %d --- fin : %d --- INDEX_PIVOT : %d --- VALEUR_PIVOT : %d TABLE : ", d, f, pivot, value);
    printTable(TAB, d,f);

    pthread_t l,r;
    int left[] = { d, i - 1, n},
        right[] = { i + 1, f, n};
    
    if (i > (d + 1))
        pthread_create(&l,NULL,ThreadHandle,& left);
    if (i < (f - 1))
        pthread_create(&r,NULL,ThreadHandle,&right);

    if (i > (d + 1))
        pthread_join(l,NULL);    
    if (i < (f - 1))
        pthread_join(r,NULL);
    
}


int main()
{
    int n = sizeof(TAB) / sizeof(int),
        Tab1[n] ,
        Tab2[n] ,
        *tab=Tab2;
    Copy(TAB,Tab1,n);
    Copy(TAB,Tab2,n);

    //SYNC
    printf("Sync Table none sorted : ");
    printTable(Tab1, 0,n-1);
    Quick(Tab1, 0, n - 1, n);
    printf("Sync Table sorted : ");
    printTable(Tab1,0,n-1);
    
    //ASYNC FORK
    printf("\nAsync Table none sorted (fork) : ");
    printTable(tab, 0,n-1);
    AsyncFQuick(&tab, 0, n - 1, n,"Table\0");
    printf("Async Table sorted (fork) : ");
    printTable(tab, 0,n-1);  
    
    //ASYNC THREADS
    printf("\nAsync Table none sorted (thread) : ");
    printTable(TAB,0 ,n-1);
    AsyncTQuick(0,n-1,n);
    printTable(TAB,0,n-1);
    printf("Async Table sorted (thread) : ");
    printTable(TAB, 0,n-1);
    return 0;
}
