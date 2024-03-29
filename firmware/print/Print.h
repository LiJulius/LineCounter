#ifndef PRINT_H
#define PRINT_H

#include "configuration/Configuration.h"

#include <iostream>
#include <string>

// TODO: Create a class for printing handling and use configuration from configuration class

// Define print, so we not have copy/paste "std::cout << x << std::endl" everywhere
#define PRINT(message) std::cout << message << std::endl
#define PRINT_ERROR(error) std::cerr << error << std::endl

// Define debug print, if kDebugPrintEnabled = true, print all debug information
#define DEBUG_PRINT(message) if(configuration::kIsDebugPrintsEnabled) {PRINT(message);} else {}

#endif // PRINT_H