#include "log_filter.h"
#include "utils.h"

void LogFilter::setLevelFilter(LogEntry::Level level) {
    level_filter = level;
}

void LogFilter::setModuleFilter(const std::string& moduleName) {
    module_filter = moduleName;
}

void LogFilter::setKeywordFilter(const std::string& keyword) {
    keyword_filter = keyword;
}

void LogFilter::clearFilters() {
    level_filter.reset();
    module_filter.reset();
    keyword_filter.reset();
}

std::vector<LogEntry> LogFilter::applyFilters(const std::vector<LogEntry>& entries) const {
    // If no filters are set, return all entries
    if (!level_filter && !module_filter && !keyword_filter) {
        return entries;
    }
    
    // Apply filters
    std::vector<LogEntry> filteredEntries;
    for (const auto& entry : entries) {
        if (matchesFilters(entry)) {
            filteredEntries.push_back(entry);
        }
    }
    
    return filteredEntries;
}

bool LogFilter::matchesFilters(const LogEntry& entry) const {
    // Check level filter
    if (level_filter && entry.getLevel() != *level_filter) {
        return false;
    }
    
    // Check module filter (not applicable for simple format yet)
    
    // Check keyword filter
    if (keyword_filter && !utils::contains(
            utils::toLower(std::string(entry.getMessage())), 
            utils::toLower(*keyword_filter))) {
        return false;
    }
    
    // If we get here, all active filters have passed
    return true;
}
