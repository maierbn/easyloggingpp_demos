/*
compile:
make demo4

run:
./demo4 -vmodule=demo4.cpp=2
 */
#include <cmath>
#include <mpi.h>
#include "easylogging++.h"
#include "initialize_logging.h"

INITIALIZE_EASYLOGGINGPP


int main(int argc, char* argv[])
{
  // initialize MPI
  MPI_Init(&argc, &argv);

  // initialize and configure Easylogging++
  initializeLogging(argc, argv, "demo4");

  // output a test message in different logging levels
  LOG(DEBUG) << "Start loop";

  // do a loop with 100 iterations
  double value = 0;
  for (int i = 0; i < 100; i++)
  {
    VLOG(1) << "Iteration no. " << i;

    // do an inner loop with 5 iterations
    for (int j = 0; j < 5; j++)
    {
      value += i-j;
      VLOG(2) << "In inner loop, iteration " << j << ", value = " << value;
    }
  }

  LOG(DEBUG) << "loop finished, value = " << value;

  // clean up MPI
  MPI_Finalize();

  return 0;
}
