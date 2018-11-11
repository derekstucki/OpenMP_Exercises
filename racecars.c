#include <stdio.h>
#include <omp.h>

void car(){
    printf(" car");
}

void race(){
    printf(" race");
}

int main ()
{
    printf("I think");
    #pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            car();
#pragma omp task
            race();
        }
    }
    printf("s are fun. \n");
}
