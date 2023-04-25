#include <iostream>
#include <omp.h>
#include <cstdio>

int main(void){
    #pragma omp parallel num_threads(12)
    {   
        int nth=omp_get_num_threads();
        int thid=omp_get_thread_num();
        //std::cout<< "Hello world from thid"<<"\t"<<thid<<std::endl;
        std::printf("hi from thid: %d out of %d.\n",thid,nth);
    }


    return 0;
}