#include "configuration/Configuration.h"
#include "error/Error.h"
#include "line_counter/LineCounter.h"
#include "print/Print.h"

#include <iostream>
#include <string>

/**
 * @brief The entry point of the program.
 * @return An integer representing the exit status.
 */
int main() {
    
    { // Destroy object after configuration is printed
        configuration::Configuration config;
        config.PrintConfiguration();
    }

    std::string folder_path {};
    error::ErrorCodes error {error::ErrorCodes::kNoError};
    while (true) {
        PRINT("Enter folder path and press enter to calculate lines of files in that folder!");

        // Raad folder path
        std::getline(std::cin, folder_path);

        // Check if path is not empty
        if (folder_path.empty()) {
            error = error::ErrorCodes::kErrorFileNotFound;
            ERROR("Folder path is empty!");
            break; // Exit loop if empty string is entered
        } else {
            // Do nothing. Continue
        }

        // Check if path is not empty
        if (!fs::exists(folder_path)) {
            error = error::ErrorCodes::kErrorFileNotFound;
            ERROR("Folder does not exist: " + folder_path);
            break; // Exit loop if empty string is entered
        } else {
            // Do nothing. Continue
        }

        // Create line counter object
        line_counter::LineCounter counter(fs::path(folder_path));

        // Count lines in folder
        error = counter.CountLines();

        // If any error occured, break
        if (error) {
            break;
        } esle {
            PRINT("Total lines in all files: " + std::to_string(counter.GetTotalLines()))
        }

    }

    return static_cast<int>(error);
}
