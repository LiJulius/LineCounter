// error.h
#ifndef ERROR_H
#define ERROR_H

namespace error_codes {
    /**
     * @brief Enumeration of error codes
     */
    enum class ErrorCodes {
        kErrorFileNotFound = 0U,		///< File not found error
        kErrorUnsupportedEncoding = 1U, ///< Unsupported encoding error
        kErrorOther = 2U,				///< Other error
    };
}

#endif // ERROR_H
