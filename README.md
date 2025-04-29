# C++ Log File Analyzer

## Overview

This project is a command-line utility written in C++ designed to parse, filter, and display information from application log files. It serves as a practical example for demonstrating C++ development workflows and GitHub Copilot features.

**Target Audience:** C++ developers, learners practicing C++ and build systems, demo for GitHub Copilot.

## Features (Core Scope)

1.  **Parsing (Progressive):**
    * Develop parsing logic incrementally to handle log files of varying complexity, using the provided sample files (`simple_events.log`, `standard_app.log`, `detailed_system.log`).
    * Target formats include:
        * **Simple (1-column):** Raw `Message Body`.
        * **Medium (3-column):** `YYYY-MM-DD HH:MM:SS LEVEL Message Body`.
        * **Complex (5+ column):** `YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) Message Body [OptionalKey=Value,...]`.
    * Store parsed data into a structured `LogEntry` object (which will evolve as more fields are handled).
2.  **Filtering:**
    * Filter log entries based on criteria provided via command-line arguments (applies when relevant fields are parsed, i.e., for medium/complex formats):
        * Log Level (`--level`)
        * Module Name (`--module`)
        * Keyword in Message Body (`--keyword`)
    * (Future: Allow combining filters).
3.  **Reporting:**
    * Print the original or filtered log entries to the standard console output in a readable format.
4.  **Command-Line Interface (CLI):**
    * Accept the input log file path as a command-line argument.
    * Accept filter criteria via command-line arguments (e.g., `--level ERROR`, `--module Database`, `--keyword "failed"`).

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
    ./build/log_analyzer data/detailed_system.log --level ERROR
    ```
* Filter by module:
    ```bash
    ./build/log_analyzer data/detailed_system.log --module NetworkInterface
    ```
* Filter by keyword in the message body:
    ```bash
    ./build/log_analyzer data/detailed_system.log --keyword "connection closed"
    ```
* Combine filters (current implementation likely processes sequentially):
    ```bash
    ./build/log_analyzer data/detailed_system.log --level WARN --module Database
    ```

## Input Format Details

* The parser expects lines following this structure:
    `YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) MessageBody [OptionalKey=Value,...]`
* **Timestamp:** Includes date, time, and milliseconds.
* **LEVEL:** One of `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`, `CRITICAL`.
* **Module:** Enclosed in `[]`.
* **ThreadID:** Enclosed in `()`.
* **MessageBody:** The rest of the primary message string.
* **Optional Key-Value Pairs:** Enclosed in `[]` at the end of the line (parsing for these might be part of future extensions).

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

This project is designed to be extensible. Some ideas for future development include:

* Implement more advanced filtering (time ranges, regex, AND/OR logic).
* Add statistical analysis features (counts, frequencies).
* Support different output formats (CSV, JSON).
* Improve parsing error handling for malformed lines.
* Add comprehensive unit tests.
* Read configuration from a file.
* Optimize for large file handling.

## Technology Stack

* **Language:** C++ (C++17 recommended)
* **Build System:** CMake
* **Compiler:** Clang / GCC
* **IDE:** Visual Studio Code