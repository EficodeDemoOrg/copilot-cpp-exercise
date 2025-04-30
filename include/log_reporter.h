#pragma once

#include "log_entry.h"
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Reporter class for formatting and displaying log entries
 * 
 * This class is responsible for formatting and displaying LogEntry objects
 * in a readable format to the console or other output streams.
 */
class LogReporter {
public:
    /**
     * @brief Default constructor
     */
    LogReporter() = default;
    
    /**
     * @brief Constructor with output stream
     * @param outStream Output stream to write to (default is std::cout)
     */
    explicit LogReporter(std::ostream& outStream);
    
    /**
     * @brief Generate a report from a collection of LogEntry objects
     * @param entries Vector of LogEntry objects to report on
     */
    void generateReport(const std::vector<LogEntry>& entries);
    
    /**
     * @brief Set the output format
     * @param format Format string (e.g., "simple", "detailed")
     */
    void setFormat(const std::string& format);
    
private:
    std::ostream& out_stream = std::cout;  // Default to std::cout
    std::string format = "simple";         // Default format
    
    /**
     * @brief Format a single LogEntry for display
     * @param entry LogEntry to format
     * @return Formatted string representation of the entry
     */
    std::string formatEntry(const LogEntry& entry) const;
};
