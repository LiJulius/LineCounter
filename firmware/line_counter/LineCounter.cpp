#include "LineCounter.h"
#include "print/Print.h"
#include "configuration/Configuration.h"

namespace line_counter {

LineCounter::LineCounter(const fs::path& directory) : m_directory(directory), m_total_lines(0) {}

LineCounter::~LineCounter() {
    for (auto& thread : m_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

LineCounter::LineCounter(const LineCounter& other) : m_directory(other.m_directory), m_total_lines(other.m_total_lines.load()) {}

LineCounter::LineCounter(LineCounter&& other) noexcept : m_directory(std::move(other.m_directory)), m_total_lines(other.m_total_lines.load()) {}

LineCounter& LineCounter::operator=(const LineCounter& other) {
    if (this != &other) {
        m_directory = other.m_directory;
        m_total_lines.store(other.m_total_lines.load());
    }
    return *this;
}

LineCounter& LineCounter::operator=(LineCounter&& other) noexcept {
    if (this != &other) {
        m_directory = std::move(other.m_directory);
        m_total_lines.store(other.m_total_lines.load());
    }
    return *this;
}

void LineCounter::CountLinesInFile(const fs::path& file_path) {
    try {
#ifdef k_check_utf8_encoding
        DEBUG_PRINT("Checking file encoding: " + file_path.string());
        std::ifstream file(file_path);
        if (!file) {
            std::cerr << "Error: Unable to open file " << file_path << std::endl;
            return;
        }

        // Check file encoding
        std::string encoding = boost::locale::util::detect_encoding(file);
        if (encoding != "UTF-8") {
            std::cerr << "Warning: File " << file_path << " is encoded in " << encoding << std::endl;
        }
#endif

#ifdef k_fault_tolerant
        DEBUG_PRINT("Processing file: " + file_path.string());
#endif

        std::ifstream file(file_path);
        if (!file) {
            std::cerr << "Error: Unable to open file " << file_path << std::endl;
            return;
        }

        int lines = 0;
        std::string line;
        while (std::getline(file, line)) {
            ++lines;
        }
        m_total_lines += lines;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void LineCounter::CountLines() {
#ifdef k_use_all_cpu_cores
    unsigned int num_cores = std::thread::hardware_concurrency();
    DEBUG_PRINT("Using " + std::to_string(num_cores) + " CPU cores");
#else
    unsigned int num_cores = 0;
#endif

    for (const auto& entry : fs::directory_iterator(m_directory)) {
        if (entry.is_regular_file()) {
            m_threads.emplace_back(&LineCounter::CountLinesInFile, this, entry.path());
        }
    }

    // Join all threads
    for (auto& thread : m_threads) {
        thread.join();
    }
}

int LineCounter::GetTotalLines() const {
    return m_total_lines;
}

} // namespace line_counter