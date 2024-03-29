#include "Configuration.h"
#include "print/Print.h"

namespace configuration {

    void Configuration::PrintConfiguration() const {
        if (configuration::kMaxCpuCoresUsed == 0U) {
            DEBUG_PRINT("Maximum alloved CPU cores is not limited");
        } else {
            DEBUG_PRINT("Maximum alloved CPU cores:" + std::to_string(configuration::kMaxCpuCoresUsed));
        }

        DEBUG_PRINT("Max alloved memory usage: " + std::to_string(configuration::kMaxMemoryUsage / 1024U / 1024U) + " MB");
    
        PrintParameterAndState("UTF8 encoding checking:", kIsUtf8EncodingCheckEnabled);
        PrintParameterAndState("Fault tolerant:", kIsFaultTolerantEnabled);
        PrintParameterAndState("Debug print:", kIsDebugPrintsEnabled);
        PrintParameterAndState("Error print:", kIsErrorPrintsEnabled);
    }

    void Configuration::PrintParameterAndState(const std::string parameter, const bool state) const {
        if (state) {
            DEBUG_PRINT(parameter + " Enabled");
        } else {
            DEBUG_PRINT(parameter + " Disabled");
        }
    }

} // namespace configuration