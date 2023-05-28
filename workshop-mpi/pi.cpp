#include "mpi.h"
#include <cstdio>
#include <cstdlib>
#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cmath>
#include <iomanip>

std::ofstream speedup;

int samples(int N,int pid);
double start_time, end_time, elapsed_time, total_elapsed_time;
/* Problem parameters */
void sample_mpi(double n, int pid, int np, int flag);

int main(int argc, char **argv)
{
  const int N = std::atoi(argv[1]);
  int flag = std::atoi(argv[2]);
  std::ofstream speedup("datos.csv", std::ios::app);

  /* MPI Variables */

  /* problem variables */
  int pid, np;
  // for(int i=0;i<ntests;i++){
  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  if (pid == 0) {
        start_time = MPI_Wtime();
  }
  
  sample_mpi(N, pid, np,flag);

      // medir tiempo final
  if (pid == 0) {
        end_time = MPI_Wtime();
    }

  
  if (pid == 0) {
     elapsed_time = end_time - start_time;
     }
  else {
        elapsed_time = 0.0; // Solo se mide el tiempo para pid 0
    }

    // Suma sobre todos los tiempos
  MPI_Reduce(&elapsed_time, &total_elapsed_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the total elapsed time on the root process (pid 0)
   if (pid == 0 && flag==0) {
     std::cout<< std::setprecision(5)<< std::scientific << np << "," << elapsed_time << std::endl;
    }

  /* finish */
  MPI_Finalize();
  //}
  //speedup << np << "\t" << avg(t,ntests) << "\t" << stddev(t,ntests) << std::endl;
  
  return 0;
}



void sample_mpi(double n, int pid, int np, int flag)
{
  /* Adjust problem size for sub-process */
  double partition = n / np;

  /* Calculate area for subproblem */
  double Nc = samples(partition, pid);

  /* Collect info and print results */
  MPI_Status status;
  int tag = 0;
  if (0 == pid) { /* Master */
    double total = Nc;
    for (int src = 1; src < np; ++src) {
      MPI_Recv(&Nc, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, &status);
      total += Nc;
    }
    if(flag==1){
    std::cout<<np<<","<<std::setprecision(5)<< std::scientific << 4*(double)total/(double)n << "," << abs(((4*(double)total/(double)n)/(double)M_PI)-1)<<std::endl;
    }
  }
  else { /* slaves only send */
    int dest = 0;
    MPI_Send(&Nc, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }
 
}



int samples(int N,int pid){

    int count = 0;
    int seed = pid;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dis(-1.0,1.0);
    for(int ii = 0; ii<N; ii++){
        double rx = dis(gen);
        double ry = dis(gen);
        if(rx*rx +ry*ry < 1){
            count++;
        }
    }
        return count;
    }



