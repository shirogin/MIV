#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned long int Fibonacci(unsigned long int n)
{
    return n <= 1 ? 1 : Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main(int argc, char **argv)
{
    clock_t starts;
    unsigned int i;
    unsigned long int elm = 0;
    FILE *F = fopen("res.csv", "w+");
    double ends;
    fprintf(F, "n, Valeur, T\n");
    for (i = 0; i < 50; i++)
    {
        //time start
        starts = clock();
        elm = Fibonacci(i);
        //time ends
        ends = (double)(clock() - starts) / CLOCKS_PER_SEC;
        printf("Fibonacci(%d) = %ld : %lf\n", i, elm, ends);
        fprintf(F, "%d, %ld, %lf\n", i, elm, ends);
    }
    fclose(F);
    return 0;
}