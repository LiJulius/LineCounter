#include "LineCounter.h"
#include "print/Print.h"
#include "configuration/Configuration.h"

#include <fstream>
#include <vector>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>

namespace line_counter {

namespace bip = boost::interprocess;

// Define a type for vector of chars with a custom allocator
using CharAllocator = bip::allocator<char, bip::managed_mapped_file::segment_manager>;
using CharVector = bip::vector<char, CharAllocator>;

LineCounter::LineCounter(const fs::path& directory) : directory_(directory), total_lines_(0U) {}

LineCounter::~LineCounter() {
    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void LineCounter::CountLinesInFile(const fs::path& file_path) {
    try {
        // Open file stream
        std::ifstream file(file_path.string(), std::ios::binary);
        if (!file) {
            ERROR("Error: Unable to open file" << file_path.string());
            return;
        }

        // Get file size
        file.seekg(0, std::ios::end);
        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        // If file size exceeds configuration::kMaxMemoryUsage, read in chunks
        if (file_size > static_cast<std::streamsize>(configuration::kMaxMemoryUsage)) {
            const std::streamsize chunk_size = static_cast<std::streamsize>(configuration::kMaxMemoryUsage);
            bip::managed_mapped_file mfile(bip::open_or_create, "mapped_file.bin", chunk_size);
            CharAllocator char_alloc(mfile.get_segment_manager());
            CharVector content(char_alloc);

            while (file_size > 0U) {
                const std::streamsize read_size = std::min(file_size, chunk_size);
                file.read(content.data(), read_size);
                content.resize(read_size);

                // Process file content to count lines
                uint32_t lines {0U};
                for (char c : content) {
                    if (c == '\n') {
                        ++lines;
                    }
                }
                total_lines_ += lines;

                file_size -= read_size;

                // Check memory usage and wait until enough memory is free
                while (mfile.get_free_memory() < static_cast<std::size_t>(chunk_size)) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100U)); // Wait for 100 milliseconds
                }
            }
        } else {
            // Allocate memory for entire file
            bip::managed_mapped_file mfile(bip::open_or_create, "mapped_file.bin", file_size);
            CharAllocator char_alloc(mfile.get_segment_manager());
            CharVector content(char_alloc);

            // Read entire file into memory
            file.read(content.data(), file_size);
            content.resize(file_size);

            // Process file content to count lines
            uint32_t lines {0U};
            for (char c : content) {
                if (c == '\n') {
                    ++lines;
                }
            }
            total_lines_ += lines;
        }
    } catch (const std::exception& error) {
        if (configuration::kIsFaultTolerantEnabled) {
            ERROR("Error: " << error.what());
        } else {
            // Do not print any catched errors
        }
    }
}

std::string LineCounter::DetectEncoding(const fs::path& file_path) const {
    std::ifstream file(file_path.string(), std::ios::binary);
    std::vector<char> buffer(1024U); // Read a small chunk of the file for encoding detection to save RAM

    file.read(buffer.data(), buffer.size());
    file.close();

    // Check for UTF-8 BOM
    if (buffer.size() >= 3 && static_cast<unsigned char>(buffer[0]) == 0xEF &&
        static_cast<unsigned char>(buffer[1]) == 0xBB && static_cast<unsigned char>(buffer[2]) == 0xBF) {
        return "UTF-8";
    }

    // Check for other encodings
    // Add your encoding detection logic here

    return "Unknown"; // Return "Unknown" if encoding cannot be determined
}

error::ErrorCodes LineCounter::CountLines() {

    const uint32_t kMaxNumberOfCores {std::thread::hardware_concurrency()};
    uint32_t used_num_cores {kMaxNumberOfCores};

    if (configuration::kMaxCpuCoresUsed != 0U) {
        used_num_cores = std::min(kMaxNumberOfCores, configuration::kMaxCpuCoresUsed);
    } else {
        // Do nothing, using max available CPU cores
    }

    DEBUG_PRINT("Using " + std::to_string(used_num_cores) + " CPU cores");

    for (const auto& entry : fs::directory_iterator(directory_)) {
        if (entry.is_regular_file()) {
            threads_.emplace_back(&LineCounter::CountLinesInFile, this, entry.path());
        }
    }

    // Join all threads
    for (auto& thread : threads_) {
        thread.join();
    }
}

uint32_t LineCounter::GetTotalLines() const {
    return total_lines_;
}

} // namespace line_counter