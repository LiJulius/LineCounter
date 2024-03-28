#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstdint>
#include <iostream>
#include <string> // Include the <string> header to use std::string

namespace configuration {

// Maximum memory usage allowed in MB
static constexpr uint32_t kMaxMemoryUsageMb {128U};

// Utilize all CPU cores. Set to 0 if max available cpu can be utilized
static constexpr uint32_t kMaxCpuCoresUsed {0U};

// Enable/disable debug prints
static constexpr bool kIsDebugPrintsEnabled {true};

// Enable/disable error prints
static constexpr bool kIsErrorPrintsEnabled {true};

// Enable/disable checking for UTF-8 encoding
static constexpr bool kIsUtf8EncodingCheckEnabled {true};

// Enable/disable fault-tolerant mode
static constexpr bool kIsFaultTolerantEnabled {true};


/**
 * @brief A class to handle configuration.
 * TODO: use configuration from a class instead of default ones listed above and add setters/getters for configuration
 */
class Configuration {
public:
    Configuration() = default;
    ~Configuration() = default;
    Configuration(Configuration const&) = delete;
    Configuration& operator=(Configuration const&) & = delete;
    Configuration(Configuration&&) = delete;
    Configuration& operator=(Configuration&&) & = delete;
    
    void PrintConfiguration() const;

private:
    /**
     * @brief Print parameter ans state
     * @param parameter the parameter name
     * @param state state of the parameter. Can be true or false
     */
    void PrintParameterAndState(const std::string parameter, const bool state) const;

    /**
     * @brief Maximum memory usage allowed in MB
     */
    uint32_t max_memory_usage_mb_ {kMaxMemoryUsageMb};

    /**
     * @brief Utilize all CPU cores. Set to 0 if max available cpu can be utilized
     */
    uint32_t max_cpu_cores_ {kMaxCpuCoresUsed};

    /**
     * @brief Enable/disable debug prints
     */
    bool is_debug_print_enabled_ {kIsDebugPrintsEnabled};

    /**
     * @brief Enable/disable error prints
     */
    bool is_error_print_enabled_ {kIsErrorPrintsEnabled};

    /**
     * @brief Enable/disable checking for UTF-8 encoding
     */
    bool is_utf8_encoding_check_enabled_ {kIsUtf8EncodingCheckEnabled};

    /**
     * @brief Enable/disable fault-tolerant mode
     */
    bool max_is_fault_tolerant_enabled_ {kIsFaultTolerantEnabled};
};

} // namespace configuration

#endif // CONFIGURATION_H