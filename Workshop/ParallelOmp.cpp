#include <iostream>

int main(void){
    #pragma omp parallel num_threads(20)
    {
        std::cout<< "Hello world"<<std::endl;
    }


    return 0;
}