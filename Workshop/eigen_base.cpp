#include <eigen3/Eigen/Dense>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
std::ofstream salidaO0;
std::ofstream salidaO3;

double multiply_eigen(int size)
  {
    srand(1); // set the random number generator seed
    // create matrices
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(size, size);

    auto start = std::chrono::steady_clock::now();
    auto C{A*B}; // MULTIPLY
    double tmp = C(0, 0); // use the matrix to make eigen compute it
    auto end = std::chrono::steady_clock::now();

    std::clog << tmp << std::endl; // use the matrix to make eigen compute it

    std::chrono::duration<double> elapsed_seconds = end-start;
    double total_time = elapsed_seconds.count();
    return total_time;
  }
double avg(std::vector<double> t, int ntests){
  double time = 0;
  for(auto & val : t){
    time += val;
  }
  return time/ntests;
}
double stddev(std::vector<double> t, int ntests){
   double mean = avg(t,ntests);
   double sum_squared_diff = 0.0;
   double diff = 0;
    for (const auto& value : t) {
        diff = value - mean;
        sum_squared_diff += diff * diff;
    }
    double variance = sum_squared_diff / (ntests);
    return std::sqrt(variance);
}
int main(int argc, char **argv) {
  int N = std::stoi(argv[1]);
  int ntests = std::stoi(argv[2]);
  int salida = std::stoi(argv[3]);
  std::string datosO0 = "datosO0-eigen-variaNsize.txt";
  std::string datosO3 = "datosO3-eigen-variaNsize.txt";
  std::ofstream salidaO0(datosO0, std::ios::app);
  std::ofstream salidaO3(datosO3, std::ios::app);
  std::vector<double> t(ntests);
  
  for(int i = 0; i < ntests; i++){
     t[i] = multiply_eigen(N);
  }
  if(salida==0){
    salidaO0 << N << "\t" << avg(t,ntests) << "\t" << stddev(t,ntests) << std::endl;}
  else {
    salidaO3 << N << "\t"<< avg(t,ntests) << "\t" << stddev(t,ntests) << std::endl;}
  
  
  salidaO0.close();
  salidaO3.close();
return 0;
}
