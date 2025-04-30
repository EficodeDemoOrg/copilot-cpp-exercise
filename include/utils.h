#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <optional>

/**
 * @brief Utility functions for string manipulation and other common tasks
 */
namespace utils {

    /**
     * @brief Split a string by delimiter
     * @param str String to split
     * @param delimiter Delimiter character
     * @return Vector of string parts
     */
    std::vector<std::string> split(const std::string& str, char delimiter);
    
    /**
     * @brief Trim whitespace from beginning and end of string
     * @param str String to trim
     * @return Trimmed string
     */
    std::string trim(const std::string& str);
    
    /**
     * @brief Convert string to lowercase
     * @param str String to convert
     * @return Lowercase string
     */
    std::string toLower(const std::string& str);
    
    /**
     * @brief Check if a string starts with a prefix
     * @param str String to check
     * @param prefix Prefix to check for
     * @return true if str starts with prefix, false otherwise
     */
    bool startsWith(const std::string& str, const std::string& prefix);
    
    /**
     * @brief Check if a string contains a substring
     * @param str String to check
     * @param substr Substring to search for
     * @return true if str contains substr, false otherwise
     */
    bool contains(const std::string& str, const std::string& substr);
    
    /**
     * @brief Parse a string into a timestamp
     * @param timeStr String containing timestamp
     * @return Optional time_point (empty if parsing fails)
     */
    std::optional<std::chrono::system_clock::time_point> parseTimestamp(const std::string& timeStr);
    
} // namespace utils
