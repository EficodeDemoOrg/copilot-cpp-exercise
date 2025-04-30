#include "log_reporter.h"
#include <iostream>

LogReporter::LogReporter(std::ostream& outStream) : out_stream(outStream) {}

void LogReporter::generateReport(const std::vector<LogEntry>& entries) {
    if (entries.empty()) {
        out_stream << "No log entries to display." << std::endl;
        return;
    }
    
    out_stream << "=== Log Report ===" << std::endl;
    out_stream << "Total entries: " << entries.size() << std::endl;
    out_stream << "==================" << std::endl;
    
    for (const auto& entry : entries) {
        out_stream << formatEntry(entry) << std::endl;
    }
    
    out_stream << "==================" << std::endl;
}

void LogReporter::setFormat(const std::string& newFormat) {
    format = newFormat;
}

std::string LogReporter::formatEntry(const LogEntry& entry) const {
    // For simple format, just return the message with a level prefix
    std::string levelStr = LogEntry::levelToString(entry.getLevel());
    
    if (format == "simple") {
        return "[" + levelStr + "] " + std::string(entry.getMessage());
    } else if (format == "detailed") {
        // For future use with complex logs
        return "[" + levelStr + "] " + std::string(entry.getMessage());
    }
    
    // Default format
    return std::string(entry.getMessage());
}
