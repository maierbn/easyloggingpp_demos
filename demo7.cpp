#include <cmath>
#include <list>
#include <vector>
#include <map>
#include <array>
#include <numeric> // iota

#include "easylogging++.h"
#include "stream_output_operators.h"

INITIALIZE_EASYLOGGINGPP

struct OwnClass
{
  int a;
  int b;
};

std::ostream &operator<<(std::ostream &stream, const OwnClass &rhs)
{
  stream << "{OwnClass a: " << rhs.a << ", b: " << rhs.b << "}";
  return stream;
}

int main(int argc, char* argv[])
{
  // initialize Easylogging++
  START_EASYLOGGINGPP(argc, argv);

  // configure format of debug output
  el::Configurations conf;
  conf.set(el::Level::Debug, el::ConfigurationType::Format, "DEBUG: %msg");
  el::Loggers::reconfigureAllLoggers(conf);

  // ---------------------------------------------------
  // demonstrate logging with STL containers

  // create some sample STL containers
  std::vector<double> vector {1.0, 2.0, 5.0};
  std::map<std::string, int> map {{"a", 1}, {"b",5}};
  std::array<double,3> array {1.0,2.0,3.0};

  std::pair<int,std::array<double,3>> pair {5,{1.0,2.0,3.0}};

  std::list<std::pair<int,std::array<double,3>>> list {{5,{1.0,2.0,3.0}}, {4,{9.0}}};

  std::map<size_t, std::tuple<int,double,int>> a{{456, {4,5.0,6}}, {789, {7,8.0,9}}};
  std::map<size_t, std::tuple<int,double,int>> b{{{123, {1,2.0,3}}}};
  std::array<std::map<size_t, std::tuple<int,double,int>>,2> c{a,b};

  std::tuple<std::string, std::array<std::map<size_t, std::tuple<int,double,int>>,2>, std::list<double>> tuple
    {"hi", c, {10.,9.,8.,7.,6.}};

  // log the containers
  LOG(DEBUG) << "vector: " << vector;
  LOG(DEBUG) << "map: " << map;
  LOG(DEBUG) << "array: " << array;
  LOG(DEBUG) << "pair: " << pair;
  LOG(DEBUG) << "list: " << list;
  LOG(DEBUG) << "tuple: " << tuple;

  std::vector<double> bigVector(1000);

  // fill vector with increasing numbers
  std::iota(bigVector.begin(), bigVector.end(), 0.0);

  LOG(DEBUG) << "bigVector: " << bigVector;

  // ---------------------------------------------------
  // demonstrate logging with own classes

  // define own class object and log
  OwnClass ownClass;
  ownClass.a = 1;
  ownClass.b = 2;

  LOG(DEBUG) << "OwnClass: " << ownClass;

  std::list<OwnClass> ownClassList;
  ownClassList.push_back(ownClass);
  ownClassList.push_back(ownClass);

  LOG(DEBUG) << "OwnClassList: " << ownClassList;

  LOG(DEBUG) << "Now testing a failed check:";
  int one = 0.999999;
  CHECK(one == 1) << "Value one is invalid";

  return 0;
}
