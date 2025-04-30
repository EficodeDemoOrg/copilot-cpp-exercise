#include "log_parser.h"
#include "utils.h"
#include <iostream>
#include <stdexcept>

LogParser::LogParser(const std::filesystem::path& filePath) : file_path(filePath) {}

void LogParser::setFilePath(const std::filesystem::path& filePath) {
    file_path = filePath;
    // Close any open file stream
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

std::vector<LogEntry> LogParser::parse() {
    std::vector<LogEntry> entries;
    
    // Open the file
    file_stream.open(file_path, std::ios::in);
    if (!file_stream.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path.string());
    }
    
    // Determine the format of the log file
    std::string format = determineFormat();
    
    // Parse each line
    std::string line;
    while (std::getline(file_stream, line)) {
        if (line.empty()) continue;  // Skip empty lines
        
        try {
            LogEntry entry = parseLogLine(line, format);
            entries.push_back(entry);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << e.what() << std::endl;
            // Continue parsing the next line
        }
    }
    
    // Close the file
    file_stream.close();
    
    return entries;
}

std::string LogParser::determineFormat() {
    // For now, we'll default to simple format
    // In the future, we could examine the first few lines to detect the format
    return "simple";
}

LogEntry LogParser::parseLogLine(const std::string& line, const std::string& format) {
    LogEntry entry;
    
    if (format == "simple") {
        entry.parseSimpleFormat(line);
    } else {
        // For future formats
        throw std::runtime_error("Unsupported log format: " + format);
    }
    
    return entry;
}
