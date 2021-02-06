#include <stdio.h>
#include <time.h>

const int Nbs1[]={1000003,2000003,4000037,8000009,16000057,32000011,64000031},
        Nbs2[]={128000003,256000001,512000009,1024000009,2048000011};

int Premier(int n){
    int p=2,i=2;
    while (i<n && p==2)
    {
        if(n%i==0) p++;
        i++;
    }
    return p==2;
}
void CalculateTime(const int *Nbs,int length){
    clock_t starts;
    int elm,i;
    double ends;
    for(i=0;i<length;i++){
        //time start
        starts = clock();
        elm=Premier(Nbs[i]);
        //time ends
        ends=(double)(clock() - starts) / CLOCKS_PER_SEC; 
        printf("%d : %s - %lf\n",Nbs[i],elm?"true":"false",ends);
    }
}
int main(int argc,char **argv){
    CalculateTime(Nbs1,7);
    CalculateTime(Nbs2,5);


    return 0;
}