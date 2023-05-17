#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <omp.h>

// Función para llenar un vector con valores aleatorios entre [-1.5, 4.5]
void fill(std::vector<double>& vec, unsigned int seed) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-1.5, 4.5);

    for (auto& element : vec) {
        element = dist(rng);
    }
}

// Función para calcular la suma total y el promedio de los elementos del vector en paralelo
double ParallelAvg(const std::vector<double>& vec) {
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < vec.size(); ++i) {
        sum += vec[i];
    }

    return sum / vec.size();
}

int main(int argc, char **argv) {
    
    unsigned int seed = std::stoi(argv[1]);  // Semilla para generar valores aleatorios
    const int vectorSize = std::stoi(argv[2]);    // Tamaño del vector
    omp_set_num_threads(8);
    // Llenar el vector con valores aleatorios
    std::vector<double> myVector(vectorSize);
    fill(myVector, seed);

    // Calcular la suma total y el promedio en paralelo
    double average = ParallelAvg(myVector);

    // Imprimir resultados
    std::cout << "Suma total: " << std::accumulate(myVector.begin(), myVector.end(), 0.0) << std::endl;
    std::cout << "Promedio: " << average << std::endl;

    return 0;
}
