#include <stdio.h>
#include <omp.h>

int global_var = 100;  // by default shared

int main() {
    int i = 10;

    // 1. shared (default for global_var and variables declared outside)
    #pragma omp parallel shared(global_var)
    {
        int tid = omp_get_thread_num();
        printf("Thread %d sees global_var = %d\n", tid, global_var);
    }

    // 2. private: each thread gets its own uninitialized ‘temp’
    #pragma omp parallel private(i)
    {
        i = omp_get_thread_num();  // i is private, so this doesn’t affect the master copy
        printf("Private i in thread %d = %d\n", omp_get_thread_num(), i);
    }
    printf("Original i after private region = %d\n", i);

    // 3. firstprivate: private with initialization from master copy
    i = 42;
    #pragma omp parallel firstprivate(i)
    {
        // each thread’s i starts at 42
        printf("Firstprivate i in thread %d starts as %d\n",
               omp_get_thread_num(), i);
        i += omp_get_thread_num();
        printf("…then modified to %d\n", i);
    }
    printf("Original i after firstprivate = %d\n", i);

    // 4. lastprivate: master’s copy updated from the “last” iteration
    int last = -1;
    #pragma omp parallel for lastprivate(last)
    for (int k = 0; k < 4; ++k) {
        last = k;
        printf("Thread %d sets last = %d\n",
               omp_get_thread_num(), last);
    }
    // after the loop, last == 3 (the final k)
    printf("last after loop = %d\n", last);

    // 5. reduction: private partial sums combined into shared sum
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int k = 1; k <= 100; ++k) {
        sum += k;  // each thread adds to its private sum
    }
    // after reduction, sum = 5050
    printf("sum of 1..100 = %d\n", sum);

    // 6. default(none): forces explicit scoping of every variable
    int a = 5, b = 10;
    #pragma omp parallel default(none) shared(a) private(b)
    {
        // b is uninitialized here—each thread’s own copy
        b = omp_get_thread_num();
        printf("Thread %d: a=%d, b=%d\n",
               omp_get_thread_num(), a, b);
    }

    return 0;
}