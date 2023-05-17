# include <iostream>
# include <omp.h>
int main(int argc, char **argv)
{
omp_set_num_threads(2);
int id = omp_get_thread_num();
int nth = omp_get_num_threads();
std::cout << "id :" << id << "\n";
std::cout << "nth :" << nth << "\n";
std::cout << "&id :" << &id << "\n";
std::cout << "&nth:" << &nth << "\n";
# pragma omp parallel
{
int id = omp_get_thread_num();
int nth = omp_get_num_threads();
std::cout << "id :" << id << "\n";
std::cout << "nth :" << nth << "\n";
std::cout << "&id :" << &id << "\n";
std::cout << "&nth:" << &nth << "\n";
}
return 0;
}

//La primera parte del codigo (antes del for) es serial, por lo que solo se usa un thread. Por esto solo aparece id=0 y nth=1. Al entrar en el for se usan los dos threads que se le dieron al programa, por lo que primero aparece el id=0. Es decir que se usa uno de los threads y despues id=1, se usa el segundo thread. en ambos casos tambien se imprime la direccion de memoria
