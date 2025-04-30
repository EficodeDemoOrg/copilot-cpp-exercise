# C++ Log File Analyzer

## Overview

This project is a command-line utility written in C++ designed to parse, filter, and display information from application log files. It serves as a practical example for demonstrating C++ development workflows and GitHub Copilot features.

**Target Audience:** C++ developers, learners practicing C++ and build systems, demo for GitHub Copilot.

## Features (Implemented)

1.  **Parsing:**
    * Parses log files of varying complexity, supporting the provided sample files (`simple_events.log`, `standard_app.log`, `detailed_system.log`).
    * Compatible with formats including:
        * **Simple:** Raw `Message Body` with basic level prefix (e.g., `[INFO] System starting up`).
        * **Complex:** `YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) Message Body`.
    * Stores parsed data into structured `LogEntry` objects with accessible fields.
2.  **Filtering:**
    * Filter log entries based on criteria provided via command-line arguments:
        * Log Level (`--level`) - Filter by severity level (TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL)
        * Keyword in Message Body (`--keyword`) - Filter entries containing a specific word or phrase
    * Multiple filters can be combined (e.g., `--level=WARN --keyword=disk` to find WARN level messages about disk)
3.  **Reporting:**
    * Outputs filtered log entries to the console in a readable format
    * Supports different output formats (currently `--format=simple` and `--format=detailed`)
4.  **Command-Line Interface (CLI):**
    * Provides a user-friendly interface via command-line arguments
    * Includes help documentation (`--help`) for quick reference

## Architecture

The application follows a modular design.

[View Architecture Diagram](docs/specs/architecture.md)

The main modules are:

* **LogEntry:** Data structure for a single log record. (`include/log_entry.h`)
* **LogParser:** Handles reading and parsing files into `LogEntry` objects. (`include/log_parser.h`, `src/log_parser.cpp`)
* **LogFilter:** Contains filtering logic. (`include/log_filter.h`, `src/log_filter.cpp`)
* **LogReporter:** Handles formatting and printing output. (`include/log_reporter.h`, `src/log_reporter.cpp`)
* **Utils:** Optional common helper functions. (`include/utils.h`, `src/utils.cpp`)
* **Main (`src/main.cpp`):** Application entry point, CLI argument parsing, orchestration.

## Getting Started

### Prerequisites

* **Operating System:** macOS (tested), Linux, or Windows with WSL.
* **C++ Compiler:** A modern C++ compiler supporting C++17 (e.g., Clang, GCC).
    * On macOS: Install Xcode Command Line Tools (`xcode-select --install`).
* **CMake:** Version 3.15 or higher (`brew install cmake` on macOS).
* **Git:** For cloning the repository.
* **Visual Studio Code:** Recommended editor.
* **VS Code Extensions:**
    * `C/C++` (Microsoft)
    * `CMake Tools` (Microsoft)
    * `GitHub Copilot` (GitHub) - *Optional, but intended for use during development.*

### Setup

1.  **Clone the repository:**
    ```bash
    git clone <your-repository-url>
    cd c++-log-analyzer # Or your chosen directory name
    ```
2.  **Ensure Prerequisites:** Make sure all the tools listed above are installed.

### Building the Project (using VS Code)

1.  **Open Folder:** Open the project's root directory (`c++-log-analyzer`) in Visual Studio Code.
2.  **Select Kit:** If prompted, or via the status bar / Command Palette (`CMake: Select a Kit`), choose your C++ compiler (e.g., the Clang kit from Xcode Command Line Tools).
3.  **Configure:** CMake Tools will typically configure the project automatically after selecting a kit. You can also trigger it manually via the Command Palette (`CMake: Configure`). Check the "Output" panel (CMake/Build channel) for messages.
4.  **Build:** Click the **Build** button in the status bar (usually says `[Build]` or similar) or use the Command Palette (`CMake: Build` or press `F7`).
5.  The compiled executable (`log_analyzer`) will be placed in the `build/` directory.

### Running the Application

Execute the compiled program from your terminal, providing the path to a log file and optional filter arguments.

1.  **Open Terminal:** Use the integrated terminal in VS Code (`Terminal > New Terminal`).
2.  **Run Command:**
    ```bash
    ./build/log_analyzer <log_file_path> [filter_options...]
    ```

**Examples:**

* Run with a specific log file:
    ```bash
    ./build/log_analyzer data/detailed_system.log
    ```
* Filter by log level:
    ```bash
    ./build/log_analyzer data/detailed_system.log --level=ERROR
    ```
* Filter by keyword in the message body:
    ```bash
    ./build/log_analyzer data/detailed_system.log --keyword=connection
    ```
* Specify output format:
    ```bash
    ./build/log_analyzer data/detailed_system.log --format=detailed
    ```
* Combine filters:
    ```bash
    ./build/log_analyzer data/detailed_system.log --level=WARN --keyword=disk
    ```
* Show help menu:
    ```bash
    ./build/log_analyzer --help
    ```

## Input Format Details

The parser currently supports multiple log formats:

### Simple Format (simple_events.log)
* Basic log entries with level and message
* Format: `[LEVEL] Message Body`
* **Examples:**
  * `[INFO] System starting up`
  * `[ERROR] Cannot connect to SMTP server 'mail.internal'`

### Detailed Format (detailed_system.log)
* More complex logs with timestamps, module information, and thread IDs
* Format: `YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) MessageBody`
* **LEVEL:** Supported levels are `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`, `CRITICAL`
* **Example:**
  * `2025-04-29 13:07:52.105 INFO [Core] (1001) System starting up. Process ID: 5678. Version: 3.0.1-beta`

## Sample Data

Sample log files with varying complexity and content are provided in the `data/` directory:

* `simple_events.log`: Single column (raw message).
* `standard_app.log`: 3 columns (Timestamp, Level, Message).
* `detailed_system.log`: 5+ columns (Timestamp.ms, Level, Module, ThreadID, Message).

It is recommended to develop and test the parsing logic progressively, starting with `simple_events.log`, then `standard_app.log`, before tackling the full complexity required for `detailed_system.log`.

## Project Structure

```
.
├── build/              # Build output directory (created by CMake)
├── data/               # Sample input log files
├── docs/
│   └── specs/
│       └── architecture.md # Architecture Diagram File
├── include/            # Header files (.h)
├── src/                # Source files (.cpp)
├── .vscode/            # VS Code settings (optional, e.g., launch.json)
├── CMakeLists.txt      # Main CMake build script
└── README.md           # This file
```

*(Note: Added the expected location of the architecture diagram to the Project Structure for clarity)*

## Potential Extensions

While the core functionality is working well, there are several opportunities for enhancement:

* **Filtering Enhancements:**
  * Add module filtering (`--module=ModuleName`) to filter by specific system components
  * Implement time-based filtering (`--from=YYYY-MM-DD`, `--to=YYYY-MM-DD`) 
  * Support regex patterns for more powerful text searches
  * Add inclusive/exclusive filter combinations (AND/OR logic)
* **Output Enhancements:**
  * Enhance the `detailed` format to show additional fields like timestamp, module, thread ID
  * Add more output formats (CSV, JSON, HTML)
  * Support output redirection to files
* **Analysis Features:**
  * Add statistical analysis (error counts by module, message frequency)
  * Generate summaries and aggregated reports
  * Visualize log patterns and trends
* **Performance & Robustness:**
  * Optimize for large file handling with stream processing
  * Improve error handling for malformed log entries
  * Add comprehensive unit tests
  * Support configuration via external files

## Technology Stack

* **Language:** C++ (C++17 recommended)
* **Build System:** CMake
* **Compiler:** Clang / GCC
* **IDE:** Visual Studio Code