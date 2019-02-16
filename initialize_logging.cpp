#include "initialize_logging.h"

#include <sstream>
#include <mpi.h>
#include "easylogging++.h"

void initializeLogging(int argc, char *argv[], std::string programName)
{
  START_EASYLOGGINGPP(argc, argv);

// color codes: https://github.com/shiena/ansicolor/blob/master/README.md
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_LIGHT_GRAY    "\x1b[90m"
#define ANSI_COLOR_LIGHT_WHITE    "\x1b[97m"
#define ANSI_COLOR_RESET   "\x1b[0m"

  std::string separator(80, '_');
  el::Configurations conf;
  conf.setToDefault();

  // determine number of ranks and own rank no
  int rankNoCommWorld = 0;
  int nRanksCommWorld = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rankNoCommWorld);
  MPI_Comm_size(MPI_COMM_WORLD, &nRanksCommWorld);
  
  // set prefix for output that includes current rank no
  std::string prefix;
  if (nRanksCommWorld > 1)
  {
    std::stringstream s;
    s << rankNoCommWorld << "/" << nRanksCommWorld << " ";
    prefix = s.str();
  }
  
#ifdef NDEBUG      // if release
  if (nRanksCommWorld > 1)
  {
    conf.setGlobally(el::ConfigurationType::Format, prefix+": %msg");
  }
  else
  {
    conf.setGlobally(el::ConfigurationType::Format, "%msg");
  }
#else
  conf.setGlobally(el::ConfigurationType::Format, prefix+"INFO : %msg");
#endif

  // set location of log files
  std::string logFilesPath = "/tmp/logs/";   // must end with '/'
  if (nRanksCommWorld > 1)
  {
    std::stringstream s;
    s << logFilesPath << rankNoCommWorld << "_" << programName << ".log";
    conf.setGlobally(el::ConfigurationType::Filename, s.str());

    // truncate logfile
    std::ofstream logfile(s.str().c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    logfile.close();
  }
  else
  {
    std::string logFilename = logFilesPath+programName+".log";
    conf.setGlobally(el::ConfigurationType::Filename, logFilename);

    // truncate logfile
    std::ofstream logfile(logFilename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    logfile.close();
  }

  // enable logging in all levels to file and stdout
  conf.setGlobally(el::ConfigurationType::Enabled, "true");
  conf.setGlobally(el::ConfigurationType::ToFile, "true");
  conf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");

  // set format for levels
  conf.set(el::Level::Debug, el::ConfigurationType::Format, prefix+"DEBUG: %msg");
  conf.set(el::Level::Trace, el::ConfigurationType::Format, prefix+"TRACE: %msg");
  conf.set(el::Level::Verbose, el::ConfigurationType::Format, ANSI_COLOR_LIGHT_WHITE "" + prefix+"VERB%vlevel: %msg" ANSI_COLOR_RESET);
  conf.set(el::Level::Warning, el::ConfigurationType::Format,
           prefix+ANSI_COLOR_YELLOW "Warning: " ANSI_COLOR_RESET "%msg");

  conf.set(el::Level::Error, el::ConfigurationType::Format,
           prefix+"ERROR: %loc %func: \n" ANSI_COLOR_RED "Error: %msg" ANSI_COLOR_RESET);

  conf.set(el::Level::Fatal, el::ConfigurationType::Format,
           "FATAL: %loc %func: \n"+std::string(ANSI_COLOR_MAGENTA)+prefix+separator
           +"\n\nFatal error: %msg\n"+separator+ANSI_COLOR_RESET+"\n");

  // disable output for ranks != 0
  if (rankNoCommWorld > 0)
  {
    conf.set(el::Level::Info, el::ConfigurationType::Enabled, "false");
    conf.set(el::Level::Warning, el::ConfigurationType::Enabled, "false");
  }

  // reconfigure all loggers
  el::Loggers::reconfigureAllLoggers(conf);
  el::Loggers::removeFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified);
}
