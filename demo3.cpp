/*
compile:
mpic++ easylogging++.cc -c -std=c++17
mpic++ demo3.cpp initialize_logging.cpp easylogging++.o -std=c++17 -o demo3
or
make demo3

run:
mpirun -n 2 ./demo3
mpirun -n 2 ./demo3_release
 */
#include <cmath>
#include <mpi.h>
#include "easylogging++.h"
#include "initialize_logging.h"

INITIALIZE_EASYLOGGINGPP

//! a test function to test the trace log
void f(int i)
{
  LOG(TRACE) << "i = " << i;
}

int main(int argc, char* argv[])
{
  // initialize MPI
  MPI_Init(&argc, &argv);

  // initialize and configure Easylogging++
  initializeLogging(argc, argv, "demo3");

  // output a test message in different logging levels
  LOG(DEBUG) << "This is a debug message.";
  LOG(DEBUG) << "This is a debug message.";
  LOG(INFO) << "This is an info message.";
  LOG(DEBUG) << "This is a debug message.";

  LOG(WARNING) << "This is a warning message.";

  LOG(DEBUG) << "This is a debug message.";
  LOG(TRACE) << "This is a trace message.";
  LOG(INFO) << "This is an info message.";
  LOG(INFO) << "This is an info message.";

  // call the function that outputs a trace log
  f(0);

  LOG(WARNING) << "This is a warning message.";
  LOG(ERROR) << "This is an error message.";
  LOG(FATAL) << "This is a fatal error message.";

  // clean up MPI
  MPI_Finalize();

  return 0;
}
