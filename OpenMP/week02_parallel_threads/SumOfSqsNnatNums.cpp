#include<bits/stdc++.h>
#include<omp.h>
#define N 9
using namespace std;

int main(){
    int tsum = 0;
    #pragma omp parallel for reduction(+:tsum) schedule(dynamic,3)
        for(int i=1;i<=N;i++){
            int tid = omp_get_thread_num();
            printf("Iteration %d done by thread[%d]\n",i,tid);
            tsum = tsum + (i*i);
        }

    printf("\nTotal sum = %d",tsum);
    return 0;
}
