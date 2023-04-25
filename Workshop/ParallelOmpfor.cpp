#include <iostream>
#include <omp.h>
#include <cstdio>

int main(void){
    int N=10000;
    double *a = new double[N];
    #pragma omp parallel for
    {   
        for(int i=0; i<N;i++){
            a[i]=2*i;
        }
        int nth=omp_get_num_threads();
        int thid=omp_get_thread_num();
        //std::cout<< "Hello world from thid"<<"\t"<<thid<<std::endl;
        std::printf("hi from thid: %d out of %d.\n",thid,nth);
    }

    delete [] a;

    return 0;
}