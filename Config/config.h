// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Maximum memory usage allowed in MB
constexpr int k_max_memory_usage_mb = 128;
// Enable debug prints
constexpr bool k_debug_prints = true;

// Enable checking for UTF-8 encoding
constexpr bool k_check_utf8_encoding = true;
// Enable fault-tolerant mode
constexpr bool k_fault_tolerant = true;
// Utilize all CPU cores
constexpr bool k_use_all_cpu_cores = true;

#endif // CONFIG_H