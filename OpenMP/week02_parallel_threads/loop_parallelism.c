#include <stdio.h>
#include <omp.h>

int main() {
    int a[10];

    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        a[i] = i * i;
        printf("Thread %d did a[%d] = %d\n", omp_get_thread_num(), i, a[i]);
    }

    return 0;
}
