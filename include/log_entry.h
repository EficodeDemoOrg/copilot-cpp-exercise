#pragma once

#include <string>
#include <map>
#include <chrono>
#include <optional>

/**
 * @brief Represents a single log entry parsed from a log file.
 * 
 * This class stores all relevant information about a log entry, including
 * timestamp, log level, module name, thread ID, message body, and optional
 * key-value pairs.
 */
class LogEntry {
public:
    // Enum for log levels
    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        UNKNOWN
    };

    // Default constructor
    LogEntry() = default;

    // Constructor with message
    LogEntry(const std::string& message);

    // Getters
    std::string_view getRawMessage() const { return raw_message; }
    std::string_view getMessage() const { return message; }
    Level getLevel() const { return level; }
    static std::string levelToString(Level level);
    static Level stringToLevel(const std::string& levelStr);

    // For simple log format in simple_events.log
    void parseSimpleFormat(const std::string& line);

    // For complex format (to be implemented later)
    // void parseComplexFormat(const std::string& line);

private:
    std::string raw_message;  // Original raw message
    std::string message;      // Parsed message content

    // Optional fields - these may not be present in simple logs but will be in complex ones
    Level level = Level::INFO;  // Default to INFO if not specified
    std::string module;
    std::string thread_id;
    std::optional<std::chrono::system_clock::time_point> timestamp;
    std::map<std::string, std::string> key_value_pairs;
};
