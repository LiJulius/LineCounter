// line_counter.h
#ifndef LINE_COUNTER_H
#define LINE_COUNTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <filesystem>
#include <boost/locale.hpp>

namespace fs = std::filesystem;

namespace line_counter {

/**
 * @brief A class to count the total number of lines in all files in a given directory.
 */
class LineCounter {
public:
    /**
     * @brief Constructs a LineCounter object with the specified directory.
     * 
     * @param directory The directory to scan for files.
     */
    LineCounter(const fs::path& directory);

    ~LineCounter() = default;
    LineCounter(LineCounter const&) = delete;
    LineCounter& operator=(LineCounter const&) & = delete;
    LineCounter(LineCounter&&) = delete;
    LineCounter& operator=(LineCounter&&) & = delete;
    
    /**
     * @brief Counts the total number of lines in all files in the directory.
     */
    void CountLines();
    
    /**
     * @brief Gets the total number of lines counted.
     * 
     * @return The total number of lines.
     */
    int GetTotalLines() const;

private:
    /**
     * @brief Helper function to count lines in a file.
     * 
     * @param file_path The path of the file to count lines from.
     */
    void CountLinesInFile(const fs::path& file_path);

private:
    fs::path directory_; ///< The directory to scan for files.
    std::atomic<int> total_lines_; ///< The total number of lines counted.
    std::vector<std::thread> threads_; ///< Vector to store threads for parallel processing.
};

} // namespace line_counter

#endif // LINE_COUNTER_H
