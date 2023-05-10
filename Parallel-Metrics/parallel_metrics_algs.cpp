#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <execution>
#include <chrono>
#include <cmath>
#include "tbb/task_scheduler_init.h"

template<typename Func> 
double time_function(Func func);
double avg(std::vector<double> t, int ntests);
double stddev(std::vector<double> t, int ntests);



int main(int argc, char **argv) {
  int N = std::stoi(argv[1]);
  int Nthreads = std::stoi(argv[2]);
  int policy = std::stoi(argv[3]); // 0 seq , 1 par , 2 par_unseq
  int ntests = std::stoi(argv[4]);
  tbb::task_scheduler_init init(Nthreads);
  std::vector<double> t(ntests);
  
  
  const long ARRAY_SIZE = N;
  std::vector<double> myArray(ARRAY_SIZE);
  std::iota(myArray.begin(), myArray.end(), 0); // fill array with 0, 1, 2, ..., ARRAY_SIZE-1
  if(policy == 0){
    // sequential execution
    auto serial = [&myArray](){return std::reduce(std::execution::seq, myArray.begin(), myArray.end());};
    std::cout << Nthreads << "\t" ;
    for(int i = 0; i < ntests; i++){
       t[i] = time_function(serial);
       std::cout << t[i] << "\t" ;
    }
     std::cout << std::endl;
  }

  else if(policy == 1){
    // parallel execution
    auto parallel = [&myArray](){return std::reduce(std::execution::par, myArray.begin(), myArray.end());};
    std::cout << Nthreads << "\t" ;
    for(int i = 0; i < ntests; i++){
       t[i] = time_function(parallel);
       std::cout << t[i] << "\t" ;
    }
     std::cout << std::endl;
  }

  else if(policy == 2){
     // parallel execution
     auto parallel_unseq = [&myArray](){return std::reduce(std::execution::par_unseq, myArray.begin(), myArray.end());};
     std::cout << Nthreads << "\t" ;
    for(int i = 0; i < ntests; i++){
       t[i] = time_function(parallel_unseq);
       std::cout << t[i] << "\t" ;
    }
    std::cout << std::endl;
  }
   
   else{
     std::cout << "Enter a valid policy" << std::endl;
   }
  return 0;
}

template<typename Func>
double time_function(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  return duration_ms/1000.0;
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
 