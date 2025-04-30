#pragma once

#include "log_entry.h"
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>

/**
 * @brief Parser for log files that creates LogEntry objects
 * 
 * This class is responsible for parsing log files and creating LogEntry objects.
 * It supports different log formats and handles any parsing errors.
 */
class LogParser {
public:
    /**
     * @brief Constructor with file path
     * @param filePath Path to the log file to parse
     */
    LogParser(const std::filesystem::path& filePath);
    
    /**
     * @brief Parse the log file and return all entries
     * @return Vector of LogEntry objects
     */
    std::vector<LogEntry> parse();
    
    /**
     * @brief Set the path to the log file
     * @param filePath Path to the log file
     */
    void setFilePath(const std::filesystem::path& filePath);
    
private:
    std::filesystem::path file_path;
    std::ifstream file_stream;
    
    /**
     * @brief Determine the format of the log file
     * @return Format type as a string (e.g., "simple", "complex")
     */
    std::string determineFormat();
    
    /**
     * @brief Parse a line of text into a LogEntry
     * @param line Line of text from the log file
     * @param format Format type of the log file
     * @return LogEntry object representing the parsed line
     */
    LogEntry parseLogLine(const std::string& line, const std::string& format);
};
