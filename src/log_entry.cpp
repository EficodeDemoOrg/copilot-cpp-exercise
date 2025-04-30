#include "log_entry.h"
#include "utils.h"
#include <algorithm>
#include <iostream>

LogEntry::LogEntry(const std::string& message) : raw_message(message), message(message) {
    // Default constructor with message only, no parsing
}

void LogEntry::parseSimpleFormat(const std::string& line) {
    raw_message = line;
    message = line;
    
    // Simple format doesn't have explicit timestamps, levels, etc.
    // But we can try to detect the level from keywords in the message
    
    std::string lowerMsg = utils::toLower(line);
    
    if (lowerMsg.find("error") != std::string::npos) {
        level = Level::ERROR;
    } else if (lowerMsg.find("warn") != std::string::npos) {
        level = Level::WARN;
    } else if (lowerMsg.find("debug") != std::string::npos) {
        level = Level::DEBUG;
    } else if (lowerMsg.find("info") != std::string::npos) {
        level = Level::INFO;
    } else if (lowerMsg.find("trace") != std::string::npos) {
        level = Level::TRACE;
    } else if (lowerMsg.find("critical") != std::string::npos) {
        level = Level::CRITICAL;
    } else {
        level = Level::INFO; // Default level
    }
}

std::string LogEntry::levelToString(Level level) {
    switch (level) {
        case Level::TRACE:    return "TRACE";
        case Level::DEBUG:    return "DEBUG";
        case Level::INFO:     return "INFO";
        case Level::WARN:     return "WARN";
        case Level::ERROR:    return "ERROR";
        case Level::CRITICAL: return "CRITICAL";
        default:              return "UNKNOWN";
    }
}

LogEntry::Level LogEntry::stringToLevel(const std::string& levelStr) {
    std::string upperLevel = levelStr;
    std::transform(upperLevel.begin(), upperLevel.end(), upperLevel.begin(), ::toupper);
    
    if (upperLevel == "TRACE")    return Level::TRACE;
    if (upperLevel == "DEBUG")    return Level::DEBUG;
    if (upperLevel == "INFO")     return Level::INFO;
    if (upperLevel == "WARN")     return Level::WARN;
    if (upperLevel == "ERROR")    return Level::ERROR;
    if (upperLevel == "CRITICAL") return Level::CRITICAL;
    
    return Level::UNKNOWN;
}
