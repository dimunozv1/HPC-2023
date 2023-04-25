#include <vector>
#include <cstdlib>
#include <chrono>
#include <stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

std::ofstream salidaO0;
std::ofstream salidaO3;

void fill(std::vector<double> & mat){
  for(auto & val : mat){
    std::srand(10);
    val=-1.0 +  2.0*std::rand();
  }
}

double multiply_simple(int size){
  srand(1);

  std::vector<double> A(size*size), B(size*size), C(size*size);
  fill(A);
  fill(B);

  auto start = std::chrono::steady_clock::now();
  for(int ii = 0;ii < size; ii++){
    for(int jj = 0;jj < size ;jj++){
      for(int kk=0; kk < size; kk++){
        C[ii*size + jj] += A[ii*size+kk]*B[ii*size + jj];

      }
    }
  }
  double tmp = C[0];
  auto end = std::chrono::steady_clock::now();

  std::cout << tmp << std::endl;  

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
  std::string datosO0 = "datosO0-simple-variaNsize.txt";
  std::string datosO3 = "datosO3-simple-variaNsize.txt";
  std::ofstream salidaO0(datosO0, std::ios::app);
  std::ofstream salidaO3(datosO3, std::ios::app);
  std::vector<double> t(ntests);
  for(int i = 0; i < ntests; i++){
     t[i] = multiply_simple(N);
  }
  if(salida==0){
    salidaO0 << N << "\t" << avg(t,ntests) << "\t" << stddev(t,ntests) << std::endl;}
  else {
    salidaO3 << N << "\t" << avg(t,ntests) << "\t" << stddev(t,ntests) << std::endl;}
  
  
  salidaO0.close();
  salidaO3.close(); 

return 0;
}
