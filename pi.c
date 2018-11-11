/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
static int max_threads = 6;
int main ()
{
    int i;
    double pi = 0.0;
    double start_time, run_time;

    step = 1.0/(double) num_steps;

    start_time = omp_get_wtime();

    omp_set_num_threads(max_threads);
    double sums[max_threads];
#pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int steps_per_thread = num_steps / num_threads;
        int ID = omp_get_thread_num();
        double sum = 0.0;
	for (i=ID * steps_per_thread + 1;i <= (ID + 1) * steps_per_thread; i++){
	    double x = (i-0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
	}
        sums[ID] = sum;

    }
    for (i=0;i<max_threads;i++){
        pi += step * sums[i];
    }
    run_time = omp_get_wtime() - start_time;
    printf("pi with %ld steps is %lf in %lf seconds\n",num_steps,pi,run_time);
}





