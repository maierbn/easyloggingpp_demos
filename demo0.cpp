/*
compile:
make demo0

or

g++ easylogging++.cc -c -std=c++17
g++ demo0.cpp easylogging++.o -std=c++17 -o demo0
 */

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
   LOG(INFO) << "My first info log using default logger";

   return 0;
}
