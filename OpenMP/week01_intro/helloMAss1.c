#include <stdio.h>
#include <omp.h>

/*
    In the command promt just run this command

    1. export OMP_NUM_THREADS=4 (in linux CMD)
    2. set OMP_NUM_THREADS=4 (in windows CMD)

    It will automatically launch your programs with
    OMP_NUM_THREADS number of threads
*/

int main() {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello from thread %d\n", tid);
    }
    return 0;
}