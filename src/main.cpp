#include "log_entry.h"
#include "log_parser.h"
#include "log_filter.h"
#include "log_reporter.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>

void printUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " [options] <log_file_path>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --level=LEVEL    Filter by log level (e.g., INFO, WARN, ERROR)" << std::endl;
    std::cout << "  --keyword=WORD   Filter by keyword in message" << std::endl;
    std::cout << "  --format=FORMAT  Output format (simple, detailed)" << std::endl;
    std::cout << "  --help           Show this help message" << std::endl;
}

int main(int argc, char* argv[]) {
    // Default values
    std::string logFilePath;
    std::optional<LogEntry::Level> filterLevel;
    std::optional<std::string> filterKeyword;
    std::string outputFormat = "simple";
    
    // Parse command line arguments
    if (argc < 2) {
        std::cerr << "Error: Missing log file path" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            printUsage(argv[0]);
            return 0;
        } else if (arg.find("--level=") == 0) {
            std::string levelStr = arg.substr(8);
            filterLevel = LogEntry::stringToLevel(levelStr);
        } else if (arg.find("--keyword=") == 0) {
            filterKeyword = arg.substr(10);
        } else if (arg.find("--format=") == 0) {
            outputFormat = arg.substr(9);
        } else if (arg[0] != '-') {
            // Assume it's the log file path
            logFilePath = arg;
        }
    }
    
    if (logFilePath.empty()) {
        std::cerr << "Error: Missing log file path" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    try {
        // Create parser, filter, and reporter
        LogParser parser(logFilePath);
        LogFilter filter;
        LogReporter reporter(std::cout);
        
        // Set up filter if needed
        if (filterLevel) {
            filter.setLevelFilter(*filterLevel);
        }
        if (filterKeyword) {
            filter.setKeywordFilter(*filterKeyword);
        }
        
        // Set reporter format
        reporter.setFormat(outputFormat);
        
        // Parse log file
        std::cout << "Parsing log file: " << logFilePath << std::endl;
        std::vector<LogEntry> entries = parser.parse();
        std::cout << "Parsed " << entries.size() << " entries." << std::endl;
        
        // Apply filters
        std::vector<LogEntry> filteredEntries = filter.applyFilters(entries);
        std::cout << "After filtering: " << filteredEntries.size() << " entries." << std::endl;
        
        // Generate report
        reporter.generateReport(filteredEntries);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}