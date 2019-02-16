/*
compile:
make demo4

run:
./demo4 -vmodule=demo4.cpp=2
 */
#include <cmath>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

// a test function f with roots +1 and +2
double f(double x)
{
  return (x-1) * (x-2);
}

// compute numerical derivative of function by central difference quotient
double df(double x, double (*f)(double))
{
  const double h = 1e-5;   //< step width

  return (f(x+h) - f(x-h)) / (2*h);
}

int main(int argc, char* argv[])
{
  START_EASYLOGGINGPP(argc, argv);

  // create two custom loggers
  el::Loggers::getLogger("control");
  el::Loggers::getLogger("numerics");

  // configure control and numerics logger to use different log files
  el::Configurations configuration;
  configuration.setToDefault();

  configuration.setGlobally(el::ConfigurationType::Filename, "control.log");
  el::Loggers::reconfigureLogger("control", configuration);

  configuration.setGlobally(el::ConfigurationType::Filename, "numerics.log");
  el::Loggers::reconfigureLogger("numerics", configuration);

  CLOG(INFO, "control") << "starting root finding program";

  // find root of function f
  const double tolerance = 1e-12;
  double x = 0.0;

  // while the function value is large than the tolerance
  while (fabs(f(x)) > tolerance)
  {
    // update position value according to Newton's scheme
    x -= f(x) / df(x,f);

    CLOG(INFO, "numerics") << "x: " << x << ", f(x): " << f(x);
  }
  CLOG(INFO, "control") << "root found: x = " << x << ", f(x) = " << f(x);

  return 0;
}
