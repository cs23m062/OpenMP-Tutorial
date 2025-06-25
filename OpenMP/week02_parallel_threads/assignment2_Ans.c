#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0, n = 100;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= n; i++) {
        int tid = omp_get_thread_num();
        printf("Thread %d handling i = %d\n", tid, i);
        sum += i * i;
    }

    printf("Sum of squares = %d\n", sum);
    return 0;
}
