#include <stdio.h>
#include <omp.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int count = 0;
    int N = 100000;

    #pragma omp parallel for reduction(+:count)
    for (int i = 1; i <= N; i++) {
        if (is_prime(i))
            count++;
    }

    printf("Number of primes between 1 and %d: %d\n", N, count);
    return 0;
}
