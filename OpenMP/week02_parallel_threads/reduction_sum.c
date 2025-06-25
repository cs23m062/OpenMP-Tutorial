#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;
    int n = 100;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= n; i++) {
        sum += i * i;
    }

    printf("Sum of squares from 1 to %d: %d\n", n, sum);
    return 0;
}
