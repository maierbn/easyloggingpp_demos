/*
compile:
make demo6
 */
#include <cmath>
#include <mpi.h>
#include "easylogging++.h"
#include "initialize_logging.h"
#include <thread>
#include <chrono>

INITIALIZE_EASYLOGGINGPP

//! function that sleeps for 1 nanosecond
int expensiveFunction()
{
  std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  return 0;
}

int main(int argc, char* argv[])
{
  // initialize MPI
  MPI_Init(&argc, &argv);

  // initialize and configure Easylogging++
  initializeLogging(argc, argv, "demo5");

  // output a test message in different logging levels
  LOG(INFO) << "Start loop";

  // produce a lot of debug outputs
  {
    TIMED_SCOPE(timerBlkObj, "debug outputs");

    long long value = 0;
    for (int i = 0; i < 1e8; i++)
    {
      LOG(DEBUG) << "i = " << i;
      value += i;
    }
    LOG(INFO) << "value: " << value;
  }

  {
    TIMED_SCOPE(timerBlkObj, "log every n");

    long long value = 0;
    for (int i = 0; i < 1e8; i++)
    {
      LOG_EVERY_N(1e7,DEBUG) << "i = " << i;
      value += i;
    }
    LOG(INFO) << "value: " << value;
  }

  {
    TIMED_SCOPE(timerBlkObj, "verbose outputs");

    long long value = 0;
    for (int i = 0; i < 1e8; i++)
    {
      VLOG(1) << "i = " << i;
      value += i;
    }
    LOG(INFO) << "value: " << value;
  }

  {
    TIMED_SCOPE(timerBlkObj, "expensive function");

    long long value = 0;
    for (int i = 0; i < 1e5; i++)
    {
      VLOG(2) << "expensive function returns " << expensiveFunction();
      value += i;
    }
    LOG(INFO) << "value: " << value;
  }

  {
    TIMED_SCOPE(timerBlkObj, "expensive function wrapped in VLOG_IS_ON");

    long long value = 0;
    for (int i = 0; i < 1e8; i++)
    {
      if (VLOG_IS_ON(2))
      {
        VLOG(2) << "expensive function returns " << expensiveFunction();
      }
      value += i;
    }
    LOG(INFO) << "value: " << value;
  }

  return 0;
}
