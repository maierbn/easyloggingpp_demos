/*
compile:
g++ easylogging++.cc -c -std=c++17
g++ demo1.cpp easylogging++.o -std=c++17 -o demo1

or

make demo1

run:
./demo1
./demo1 --default-log-file=log.txt
 */

#include <cmath>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
  START_EASYLOGGINGPP(argc, argv);

  double a = std::sqrt(2);

  LOG(INFO) << "computation complete";

  LOG(INFO) << "a = " << a << ", a^2 = " << a*a << std::endl;

  LOG(INFO) << "end";

  return 0;
}
