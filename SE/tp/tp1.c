//debut fin PO
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <sys/mman.h>
#include <unistd.h> 
#include <pthread.h> 

int TAB[] = {1, 12, 7,  57, 2, 10, 54, 47, 0, 16},
    n,
    *Tab1,
    *Tab2;

void printTable(int Tab[], int d,int f)
{
    printf("[ ");
    for (int i = d; i < f; i++)
        printf("%d, ", Tab[i]);
    printf("%d ]\n", Tab[f]);
}
void printDetail(int Tab[],int d,int f,int index,int pivot){
    printf("debut : %d --- fin : %d --- INDEX_PIVOT : %d --- VALEUR_PIVOT : %d TABLE : ", d, f, index,pivot);
    printTable(TAB, d,f);
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
void Partition(int TAB[],int pivot,int *i,int *j){
    while ((*i) != (*j))
    {
        while (TAB[*i] < pivot) (*i)++;
        while (TAB[*j] > pivot) (*j)--;
        swap(&TAB[*j], &TAB[*i]);
    }
}
void Quick( int d, int f)
{
    int index=(f + d) / 2,pivot = Tab1[index], i = d, j = f;
    Partition(Tab1,pivot,&i,&j);

    printDetail(Tab1,d,f,index,pivot);
    
    if (i > (d + 1))
        Quick(d, i - 1);
    if (i < (f - 1))
        Quick(i + 1, f);
}
void AsyncFQuick(int d, int f)
{
    int index=(f + d) / 2,pivot = Tab2[index], i = d, j = f;
    Partition(Tab2,pivot,&i,&j);
    
    printDetail(Tab2,d,f,index,pivot);
    
    if (i > (d + 1) && (fork()==0)){
        AsyncFQuick( d, i - 1);
        exit(EXIT_SUCCESS);
	}
    if (i < (f - 1) && (fork()==0)){
        AsyncFQuick( i + 1, f);
        exit(EXIT_SUCCESS);
	}

    wait(NULL);
	wait(NULL);
}
void AsyncTQuick( int d, int f);
void *ThreadHandle(void *args){
    int *var=(int *) args;
    AsyncTQuick(var[0],var[1]);
    return NULL;
}
void AsyncTQuick(int d, int f)
{
    int index=(f + d) / 2,pivot = TAB[index], i = d, j = f;
    Partition(TAB,pivot,&i,&j);

    printDetail(TAB,d,f,index,pivot);

    pthread_t l,r;
    int left[] = { d, i - 1},
        right[] = { i + 1, f};
    
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
    n = sizeof(TAB) / sizeof(int);
    Tab1=(int *)malloc(sizeof(int)*n);
    Tab2=(int *)malloc(sizeof(int)*n);
    Copy(TAB,Tab1,n);
    
    //SYNC
    printf("Sync Table none sorted : ");
    printTable(Tab1, 0,n-1);
    Quick( 0, n - 1);
    printf("Sync Table sorted : ");
    printTable(Tab1,0,n-1);
    
    Tab2=mmap(NULL,sizeof *Tab2,PROT_READ | PROT_WRITE,MAP_SHARED| MAP_ANONYMOUS,-1,0);
    Copy(TAB,Tab2,n);
    //ASYNC FORK
    printf("\nAsync Table none sorted (fork) : ");
    printTable(Tab2, 0,n-1);
    AsyncFQuick( 0, n - 1);
    printf("Async Table sorted (fork) : ");
    printTable(Tab2, 0,n-1);  
    munmap(Tab2,sizeof *Tab2);
    
    //ASYNC THREADS
    printf("\nAsync Table none sorted (thread) : ");
    printTable(TAB,0 ,n-1);
    AsyncTQuick(0,n-1);
    printf("Async Table sorted (thread) : ");
    printTable(TAB, 0,n-1);
    return 0;
}
