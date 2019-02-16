/*
compile:
g++ easylogging++.cc -c -std=c++17
g++ demo2.cpp easylogging++.o -std=c++17 -o demo2

or

make demo2

run:
./demo2
 */
#include <cmath>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

//! a test function to test the trace log
void f(int i)
{
  LOG(TRACE) << "i = " << i;
}

int main(int argc, char* argv[])
{
  START_EASYLOGGINGPP(argc, argv);

  // Load configuration from file
  el::Configurations configuration("configuration.conf");

  // Apply configuration
  el::Loggers::reconfigureAllLoggers(configuration);

  // output a test message in different logging levels
  LOG(DEBUG) << "hi";
  LOG(TRACE) << "hi";
  LOG(INFO) << "hi";

  // call the function that outputs a trace log
  f(0);

  LOG(WARNING) << "hi";
  LOG(ERROR) << "hi";
  LOG(FATAL) << "hi";

  LOG(INFO) << "You won't see this.";

  return 0;
}
