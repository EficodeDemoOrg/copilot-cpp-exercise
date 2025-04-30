#pragma once

#include "log_entry.h"
#include <vector>
#include <string>
#include <functional>
#include <optional>

/**
 * @brief Filter class for filtering log entries based on various criteria
 * 
 * This class provides functionality to filter LogEntry objects based on 
 * different criteria such as log level, module, and message content.
 */
class LogFilter {
public:
    /**
     * @brief Default constructor
     */
    LogFilter() = default;
    
    /**
     * @brief Set level filter
     * @param level Level to filter by
     */
    void setLevelFilter(LogEntry::Level level);
    
    /**
     * @brief Set module filter
     * @param moduleName Module name to filter by
     */
    void setModuleFilter(const std::string& moduleName);
    
    /**
     * @brief Set keyword filter
     * @param keyword Keyword to search for in messages
     */
    void setKeywordFilter(const std::string& keyword);
    
    /**
     * @brief Clear all filters
     */
    void clearFilters();
    
    /**
     * @brief Apply filters to a collection of LogEntry objects
     * @param entries Vector of LogEntry objects to filter
     * @return Vector of filtered LogEntry objects
     */
    std::vector<LogEntry> applyFilters(const std::vector<LogEntry>& entries) const;
    
private:
    using LevelType = LogEntry::Level; // Alias for the nested enum type
    std::optional<LogEntry::Level> level_filter; // Use the full type instead of the alias
    std::optional<std::string> module_filter;
    std::optional<std::string> keyword_filter;
    
    /**
     * @brief Check if an entry matches all active filters
     * @param entry LogEntry to check
     * @return true if the entry matches all active filters, false otherwise
     */
    bool matchesFilters(const LogEntry& entry) const;
};
