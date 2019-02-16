
#include <iostream>

//! Initialize and configure the Easylogging++ library.
//! This sets message formats for the logging levels. It assumes that the program uses MPI and
//! MPI_Init was called beforehand. Logs are written to /tmp/logs/<programName>.log
//! @param argc: number of command line arguments
//! @param argv: command line arguments
//! @param programName: name of the program, will be used for the filename of the log
void initializeLogging(int argc, char *argv[], std::string programName="program");
