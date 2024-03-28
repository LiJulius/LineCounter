// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

namespace configuration {

// Maximum memory usage allowed in MB
static constexpr uint32_t kMaxMemoryUsageMb {128U};

// Utilize all CPU cores. Set to 0 if max available cpu can be utilized
static constexpr bool kMaxCpuCoresUsed {true};

// Enable/disable debug prints
static constexpr bool kIsDebugPrintsEnabled {true};

// Enable/disable checking for UTF-8 encoding
static constexpr bool kIsUtf8EncodingCheckEnabled {true};

// Enable/disable fault-tolerant mode
static constexpr bool kIsFaultTolerantEnabled {true};

} // namespace configuration

#endif // CONFIG_H