/*
compile:
make demox

run:
mpirun -n 2 ./demox
 */
#include <cmath>
#include "easylogging++.h"
#include <mpi.h>
#include <thread>
#include <chrono>

INITIALIZE_EASYLOGGINGPP

void computeData(int i, std::pair<int,float> &value)
{
  for (int j = 0; j < i; j++)
  {
    value.second += std::pow(i,1./(j+1));
    value.first++;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand()%100));
  }
}

int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);

  int nIterations = 10;

  const bool debug_output_1 = true;
  const bool debug_output_2 = true;
  const bool debug_output_3 = true;

  std::vector<std::pair<int,float>> data(nIterations, std::pair<int,float>{});
  int value = -10;

  if (debug_output_1)
  {
    int rankNo = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankNo);
    std::cout << "start loop with " << nIterations << " iterations on rank " << rankNo << std::endl;
  }

  for (int i = 0; i < nIterations; i++)
  {
    // std::cout << "begin iteration " << i << std::endl;
    if (debug_output_2)
    {
      int rankNo = 0;
      MPI_Comm_rank(MPI_COMM_WORLD, &rankNo);
      std::cout << "this is rank " << rankNo << ", current value vector: ";
      for (std::vector<std::pair<int,float>>::const_iterator iter = data.begin(); iter != data.end(); iter++)
      {
        std::cout << " [" << iter->first << "," << iter->second << "], ";
      }
      std::cout << std::endl;
    }

    // std::cout << "now call computeData, in line 40 of code" << std::endl;
    computeData(2*i, data[i]);

    //std::cout << data[j].first << "," << data[j].second << std::endl;

    if (data[i].first < 0)
    {
      std::cout << "FATAL ERROR! This should not happen. In line 49 of file!";
      MPI_Abort(MPI_COMM_WORLD, 0);
    }

    value += i;

    if (debug_output_1)
    {
      if (i % 1000 == 0)
      {
        int rankNo = 0;
        MPI_Comm_rank(MPI_COMM_WORLD, &rankNo);
        std::cout << "i: " << i << ", current value: " << value << " (on rank " << rankNo << ")" << std::endl;
      }
    }
  }

  // clean up MPI
  MPI_Finalize();

  return 0;
}
