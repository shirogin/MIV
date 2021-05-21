#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <pthread.h>
int G=10;
void *thFunc(void *args){
    int *x=(int *)args;
    int y=x[0],z=x[1];
    
    pthread_t p,q;
    int m=(z+y)/2;
    if((z-y)>1){
        int T[]={y,m-1},
            Y[]={ m,z};
        pthread_create(&p,NULL,&thFunc,(void *)T);
        pthread_create(&q,NULL,&thFunc,(void *)Y);
        pthread_join(p,NULL);
        pthread_join(q,NULL);
    }
    
    G=y*z;
    printf("G: %d |",G);
    for (int i = y; i <= z; i++)
    {
        printf("%d ",i);
    }
    printf("\n"); 
    return NULL;
}
int main(){
    pthread_t pidd;
    int x[]={-5,5};
    pthread_create(&pidd,NULL,&thFunc,(void *)x);
    pthread_join(pidd,NULL);
    return 0;
}