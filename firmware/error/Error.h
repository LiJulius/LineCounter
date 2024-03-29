// error.h
#ifndef ERROR_H
#define ERROR_H

#include "print/Print.h"
#include "configuration/Configuration.h"

#include <cstdint>
#include <iostream>
#include <string>

// TODO: Create a class for error handling and use configuration from configuration class
#define ERROR(error) \
    if(configuration::kIsErrorPrintsEnabled) { \
        std::stringstream errorStream; \
        errorStream << "ERROR: File: " << __FILE__ << ", Line: " << __LINE__ << ", Error: " << error; \
        PRINT_ERROR(errorStream.str()); \
    }

namespace error {
    /**
     * @brief Enum class that defines all possible error codes
     */
    enum class ErrorCodes : uint8_t {
        kNoError = 0U,		            ///< No Error
        kFolderPathIsEmpty = 1U,		///< Folder path is empty

        kErrorFileNotFound = 2U,		///< File not found error
        kErrorUnsupportedEncoding = 3U, ///< Unsupported encoding error
        kErrorOther = 4U,				///< Other error
    };
}

#endif // ERROR_H
