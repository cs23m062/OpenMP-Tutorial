#include<omp.h>
#include<bits/stdc++.h>
using namespace std;

int is_prime(int n){

    if(n<=1)
        return 0;

    int flag = 1;
    int limit = ceil(sqrt(n));  
    #pragma omp parallel for
    for(int i=2; i<n;i++){
        if(flag && n%i==0){
            cout<<"Thread["<<omp_get_thread_num()<<"], Found that\n";
            flag = 0;
        }
    }
    return flag;
}

int main(){
    
    int n;
    cout<<"Enter a number to check for prime\n";
    cin>>n;

    cout<<"Max Threads in Machine\n"<<omp_get_max_threads()<<endl;
    omp_set_num_threads(min(n, omp_get_max_threads()));
    if(is_prime(n))
        cout<<"Yes this is prime";
    else
        cout<<"No, This is not prime";
    return 0;
}