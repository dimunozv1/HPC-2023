#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <execution>
#include <chrono>
#include "tbb/task_scheduler_init.h"

template<typename Func> 
void time_function(Func func, int threads);

int main(int argc, char **argv) {
  int N = std::stoi(argv[1]);
  int Nthreads = std::stoi(argv[2]);
  int policy = std::stoi(argv[3]); // 0 seq , 1 par , 2 par_unseq
  tbb::task_scheduler_init init(Nthreads);
  
  
  const long ARRAY_SIZE = N;
  std::vector<double> myArray(ARRAY_SIZE);
  std::iota(myArray.begin(), myArray.end(), 0); // fill array with 0, 1, 2, ..., ARRAY_SIZE-1
  if(policy == 0){
    // sequential execution
    auto serial = [&myArray](){return std::accumulate(myArray.begin(), myArray.end(), 0.0);};
    time_function(serial ,Nthreads);
  }

  else if(policy == 1){
    // parallel execution
    auto parallel = [&myArray](){return std::reduce(std::execution::par, myArray.begin(), myArray.end());};
    time_function(parallel ,Nthreads);
  }

  else if(policy == 2){
     // parallel execution
     auto parallel_unseq = [&myArray](){return std::reduce(std::execution::par_unseq, myArray.begin(), myArray.end());};
     time_function(parallel_unseq ,Nthreads);
  }
   
   else{
     std::cout << "Enter a valid policy" << std::endl;
   }
  return 0;
}

template<typename Func>
void time_function(Func func, int threads) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << threads << "\t"  << duration_ms/1000.0  << std::endl;
}
