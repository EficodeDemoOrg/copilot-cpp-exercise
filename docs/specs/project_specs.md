# C++ Log File Analyzer

## Overview

This project is a command-line utility written in C++ designed to parse, filter, and display information from application log files. It serves as a practical example for demonstrating C++ development workflows and GitHub Copilot features.

**Target Audience:** C++ developers, learners practicing C++ and build systems, demo for GitHub Copilot.

## Core Features (Initial Scope)

1.  **Parsing:**
    * Read log entries from specified input files.
    * Parse entries conforming to the format:
        `YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) MessageBody [Key1=Value1, Key2="Value with spaces", ...]`
    * Store parsed data in a `LogEntry` struct/class. Handle potential variations like missing optional key-value data.
2.  **Filtering:**
    * Filter log entries based on `LEVEL` (e.g., show only ERROR, WARN).
    * Filter log entries based on `Module` name.
    * Filter log entries based on a simple keyword search within the `MessageBody`.
    * Allow combining filters (e.g., show ERRORs from the 'Database' module - maybe implement sequentially first).
3.  **Reporting:**
    * Print the filtered log entries to the standard console output in a readable format.
4.  **Command-Line Interface (CLI):**
    * Accept the input log file path as a command-line argument.
    * Accept filter criteria via command-line arguments (e.g., `--level ERROR`, `--module Database`, `--keyword "failed"`).

## Architecture Modules

* **LogEntry:** Data structure for a single log record. (`log_entry.h`)
* **LogParser:** Handles reading and parsing files into `LogEntry` objects. (`log_parser.h/.cpp`)
* **LogFilter:** Contains filtering logic. (`log_filter.h/.cpp`)
* **LogReporter:** Handles formatting and printing output. (`log_reporter.h/.cpp`)
* **Utils:** Optional common helper functions (e.g., string splitting, timestamp parsing). (`utils.h/.cpp`)
* **Main (`main.cpp`):** Application entry point, CLI argument parsing, orchestration.

*(See Architecture Diagram above)*

## Input Format

* Log files contain text lines following the structure:
    `YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) MessageBody [OptionalKey=Value,...]`
* Example valid levels: `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`, `CRITICAL`
* Sample log files (`data/` directory):
    * `system_complex.log` (contains mixed entries with the new format)
    * *(Potentially add more specific ones later)*

## Output Format

* Filtered log entries printed to the console, maintaining the original fields for clarity (or potentially a simplified format).

## Potential Extensions (Open-ended)

* Implement more advanced filtering (time ranges, regex matching, combining filters with AND/OR logic).
* Add statistical analysis (e.g., count entries per level/module, frequency of specific messages).
* Support different output formats (CSV, JSON).
* Improve error handling for parsing malformed lines or file I/O issues.
* Add unit tests for parser and filter logic.
* Read configuration from a file instead of only CLI args.
* Handle larger files more efficiently (e.g., process line-by-line instead of loading all into memory).

## Technology Stack

* **Language:** C++ (using C++17 or C++20 features recommended)
* **Build System:** CMake
* **Compiler:** Clang (via Xcode Command Line Tools) or GCC
* **Development Environment:** Visual Studio Code with C/C++, CMake Tools, and GitHub Copilot extensions.