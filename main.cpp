// main.cpp
#include "LineCounter.h"
#include "Error.h"

/**
 * @brief The entry point of the program.
 * @return An integer representing the exit status.
 */
int main() {
#ifdef ENABLE_DEBUG_PRINTS
    DEBUG_PRINT("Debug prints enabled");
#endif

#ifdef MAX_ALLOVED_MEMORY_USAGE_MB
    DEBUG_PRINT("Max alloved memory usage: " + std::to_string(MAX_MEMORY_USAGE_MB) + " MB");
#endif

    fs::path directory(".");
    LineCounter counter();
    counter.CountLines(directory);
    std::cout << "Total lines in all files: " << counter.GetTotalLines() << std::endl;

    return static_cast<int>(ErrorCodes::ErrorCode::kErrorFileNotFound);
}
