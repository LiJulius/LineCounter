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
#include "config/Config.h"

namespace fs = std::filesystem;

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
    explicit LineCounter(const fs::path& directory);
    
    /**
     * @brief Destructor for the LineCounter object.
     */
    ~LineCounter();
    
    /**
     * @brief Copy constructor.
     * 
     * @param other The LineCounter object to copy from.
     */
    LineCounter(const LineCounter& other);
    
    /**
     * @brief Move constructor.
     * 
     * @param other The LineCounter object to move from.
     */
    LineCounter(LineCounter&& other) noexcept;
    
    /**
     * @brief Copy assignment operator.
     * 
     * @param other The LineCounter object to copy from.
     * @return A reference to the LineCounter object.
     */
    LineCounter& operator=(const LineCounter& other);
    
    /**
     * @brief Move assignment operator.
     * 
     * @param other The LineCounter object to move from.
     * @return A reference to the LineCounter object.
     */
    LineCounter& operator=(LineCounter&& other) noexcept;
    
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
    fs::path m_directory; ///< The directory to scan for files.
    std::atomic<int> m_total_lines; ///< The total number of lines counted.
    std::vector<std::thread> m_threads; ///< Vector to store threads for parallel processing.
};

#endif // LINE_COUNTER_H
