#include <stdio.h>
#include <omp.h>

#define N 20
#define K 20
#define M 20

int main() {
    double A[N][K], B[K][M], C[N][M];

    // Initialize matrices
    for (int i = 0; i < N; i++)
        for (int k = 0; k < K; k++)
            A[i][k] = i + k;

    for (int k = 0; k < K; k++)
        for (int j = 0; j < M; j++)
            B[k][j] = k - j;

    // Initialize result matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = 0.0;

    // Parallel matrix multiplication using collapse
    printf("Starting matrix multiplication...\n");
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Print a few results to verify
    printf("C[0][0] = %f\n", C[0][0]);
    printf("C[N-1][M-1] = %f\n", C[N-1][M-1]);

    return 0;
}
