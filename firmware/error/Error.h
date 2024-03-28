// error.h
#ifndef ERROR_H
#define ERROR_H

#include <cstdint>

namespace error_codes {
    /**
     * @brief Enum class that defines all possible error codes
     */
    enum class ErrorCodes : uint8_t {
        kErrorFileNotFound = 0U,		///< File not found error
        kErrorUnsupportedEncoding = 1U, ///< Unsupported encoding error
        kErrorOther = 2U,				///< Other error
    };
}

#endif // ERROR_H
