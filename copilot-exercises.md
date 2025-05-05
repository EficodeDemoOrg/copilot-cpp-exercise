# GitHub Copilot Exercises: Building the C++ Log Analyzer

This document provides a series of exercises designed to help you learn and practice using GitHub Copilot features to build the C++ Log Analyzer application starting from a basic project scaffold. We will cover generating initial structures, implementing core functionality progressively, adding features, testing, and exploring the codebase as it develops.

**Key Copilot Interaction Points:**

* **Chat View:** Used for asking questions, generating code/tests/docs, and initiating actions. Modes like "Ask" (default), "Edits", and "Agent" might be selectable via a dropdown menu within the Chat view interface itself.
* **Inline Chat:** Quick chat directly in the editor (Default: `Cmd+I` / `Ctrl+I` on macOS), often used for quick explanations or edits on selected code. Allows reviewing multiple suggestions using keyboard shortcuts (e.g., `Alt+]`/`Option+]` or check the Command Palette for "Copilot: View Next/Previous Suggestion").
* **Participants (`@` references):** Used to bring specific, broad contexts into the chat, such as the entire workspace (`@workspace`) or the VS Code environment itself (`@vscode`). **Important Limitation:** You can only use **one participant** (e.g., `@workspace` OR `@vscode`) in a single chat prompt.
* **Variables (`#` references):** Used to provide more granular context to Copilot (e.g., files `#file`, selections `#selection`, symbols `#sym`, symbol usages/definitions `#usage`, changes `#changes`, codebase structure `#codebase`, web content `#fetch`, last terminal command `#terminalLastCommand`, terminal selection `#terminalSelection`). Variables *can* be combined with a participant (e.g., `@workspace #file:src/log_parser.cpp`).
    * **Interactive Selection:** For files, folders, symbols (`#sym`), and usage queries (`#usage`), you typically type `#` and then start typing the name; VS Code's UI will suggest matching items from your workspace for you to select easily (e.g., typing `#LogP` might suggest the `src/log_parser.cpp` file and the `LogParser` class symbol).
    * **Drag and Drop:** You can also often drag files or folders directly from the VS Code Explorer into the Chat input area to add them as context.
* **Slash Commands:** Used within the Chat view or inline chat to direct Copilot's actions (e.g., `/explain`, `/tests`, `/fix`, `/new`).
* **Code Completion:** Automatic suggestions as you type C++ code.
* **Custom Instructions:** Files like `.github/copilot-instructions.md` can guide Copilot's suggestions for the workspace.

**Note on `@workspace` vs `#codebase` and Participant Usage:**

(This section remains the same as before - keep it for reference)

Both `@workspace` and `#codebase` provide Copilot with context about your entire project or workspace files, serving **essentially the same core function**. However, their usage context can differ:
* `@workspace` is the standard **participant** for general questions about the project, typically used within the default "Ask" mode of the Chat view. As a participant, it adheres to the **one-participant-per-prompt** rule.
* `#codebase` is a **variable** that also refers to the workspace context. You might observe that `#codebase` is particularly effective or required when using specific modes like "Edits" or "Agent" (`/new`), where a deeper analysis or generation based on the entire codebase structure is required. Since it's a variable, it doesn't conflict with the one-participant rule if you needed to use `@vscode` alongside workspace context (though combining `@vscode` and `#codebase` is an uncommon scenario).
These exercises generally use `@workspace` for broad "Ask" queries and `#codebase` when broad context seems needed for Agent/Edit tasks, reflecting common patterns and the potential need for `#codebase` in those specific modes. Feel free to experiment to see what works best in your specific scenario.

**Prerequisites:**

* Visual Studio Code installed on your macOS.
* C++ Toolchain (Xcode Command Line Tools with Clang) installed.
* CMake installed.
* GitHub Copilot and Copilot Chat extensions installed and configured in VS Code.
* The C++ Log Analyzer project **scaffolding** opened in VS Code (contains folders `src`, `include`, `data`, `docs`, `build`; files `README.md`, `CMakeLists.txt`, sample logs in `data/`, potentially empty `.h`/`.cpp` files).
* The project successfully configured and built at least once using CMake Tools (even with just the minimal `main.cpp`).
* An integrated terminal open within VS Code (e.g., View > Terminal).
* Basic understanding of C++ (including STL like `string`, `vector`, `fstream`) and CMake (`CMakeLists.txt`).
* Sample log files (`simple_events.log`, `standard_app.log`, `detailed_system.log`, `malformatted_entries.log`) placed in the `data/` directory.

---

## Section 1: Project Setup & Initial Structure Generation

**Goal:** Understand the project goal from the README and use Copilot to generate the initial C++ class/struct declarations and skeleton implementations based on the architecture described. Ensure the basic project structure compiles.

---

### Exercise 1.1: Understanding the Goal (`@workspace`, `/explain`)

* **Purpose:** To confirm Copilot can understand the project's intent from the existing `README.md`.
* **Aim:** Practice using `@workspace` for initial project context understanding.
* **Steps:**
    1. Open the Copilot Chat view in VS Code. Ensure the mode is "Ask".
    2. In the chat input, type the following prompt and press Enter:
        ```
        @workspace /explain Based *only* on the README.md file, what is the main purpose of this C++ project? What are the planned core features and architecture modules mentioned?
        ```
    3. Review Copilot's explanation to ensure it aligns with the README.

### Exercise 1.2: Generating Header Files (`/new` or Ask/Copy)

* **Purpose:** To create the initial declarations for the core data structure and modules.
* **Aim:** Practice generating header files (`.h`) with class/struct declarations using Copilot.
* **Steps:**
    1. **Generate `LogEntry.h`:**
        * Open Copilot Chat. Use the `/new` command (or Ask mode and copy the code):
            ```
            /new Create a new C++ header file named 'log_entry.h' inside the 'include/' directory. Define a struct or class named 'LogEntry' based on the README's description of the complex log format (`YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) MessageBody [OptionalKey=Value,...]`). Include appropriate data members (e.g., using std::string for most, maybe an enum for LEVEL, std::chrono::time_point for timestamp). Add necessary standard library includes (like <string>, <vector>, <chrono>, <map> for key-value pairs if doing now). Include header guards (#ifndef/#define/#endif). Add basic Doxygen comments. For now, make members public or provide a simple constructor.
            ```
        * Review the proposed file creation/content and approve or copy/paste into `include/log_entry.h`.
    2. **Generate `LogParser.h`:**
        * Similar to step 1, use `/new` or Ask mode:
            ```
            /new Create a new C++ header file named 'log_parser.h' inside 'include/'. Define a class 'LogParser'. Include the 'log_entry.h' header. Declare a public method like 'std::vector<LogEntry> parseLogFile(const std::string& filename) const;'. Add necessary includes (<vector>, <string>), header guards, and basic Doxygen comments. Consider adding a private helper method declaration like 'std::optional<LogEntry> parseLine(const std::string& line) const;' (include <optional>).
            ```
        * Review and save to `include/log_parser.h`.
    3. **Generate `LogFilter.h` and `LogReporter.h`:**
        * Repeat the process for `LogFilter` (e.g., declare `filterEntries(const std::vector<LogEntry>& entries, /* filter criteria */)`) and `LogReporter` (e.g., declare `printReport(const std::vector<LogEntry>& entries)`). Place them in the `include/` directory. Remember header guards and basic includes.

### Exercise 1.3: Generating Skeleton Source Files (`/new` or Ask/Copy)

* **Purpose:** To create the basic `.cpp` files with necessary includes and empty method definitions.
* **Aim:** Practice generating skeleton implementations.
* **Steps:**
    1. **Generate `log_parser.cpp`:**
        * Open Copilot Chat.
            ```
            /new Create a new C++ source file named 'log_parser.cpp' inside the 'src/' directory. Include the corresponding header "log_parser.h". Provide empty implementations (just return an empty vector or nullopt for now) for the methods declared in the header (parseLogFile, parseLine). Include necessary standard library headers mentioned in the header or needed for implementation stubs.
            ```
        * Review and save to `src/log_parser.cpp`.
    2. **Generate `log_filter.cpp` and `log_reporter.cpp`:**
        * Repeat the process for `LogFilter` and `LogReporter`, creating `.cpp` files in `src/` with includes and empty method bodies.

### Exercise 1.4: Updating CMake (`#file` CMakeLists.txt, Edits/Ask)

* **Purpose:** To tell the build system about the new source files.
* **Aim:** Practice using Copilot to modify `CMakeLists.txt`.
* **Steps:**
    1. Open `CMakeLists.txt`.
    2. Open Copilot Chat.
    3. Provide context and ask for the change:
        ```
        #file:CMakeLists.txt /explain Modify the 'add_executable(log_analyzer ...)' command to include the following source files from the 'src/' directory: log_parser.cpp, log_filter.cpp, log_reporter.cpp. Show me the updated command.
        ```
    4. Review the suggested change to the `add_executable` line. Manually update `CMakeLists.txt` or use Edits mode on that specific line.

### Exercise 1.5: Initial Build Verification

* **Purpose:** To ensure the project skeleton with new files compiles without errors.
* **Aim:** Practice the basic build process.
* **Steps:**
    1. Use VS Code's CMake Tools integration:
        * Ensure a Kit is selected (Status bar or `Cmd+Shift+P -> CMake: Select a Kit`).
        * Run Configure (`Cmd+Shift+P -> CMake: Configure` or wait for automatic).
        * Click the **Build** button in the status bar or run `Cmd+Shift+P -> CMake: Build`.
    2. Check the "Output" panel. The build should succeed (linking the empty implementations). If not, use Copilot Chat to help diagnose compiler/linker errors based on the output.

---

## Section 2: Implement Core Parsing Logic (Simple Format)

**Goal:** Implement the basic functionality to read and parse the simplest log format (`simple_events.log`).

---

### Exercise 2.1: Implement `LogEntry` Structure (Simple)

* **Purpose:** Define the data members needed for the simplest log format.
* **Aim:** Use code completion to add members.
* **Steps:**
    1. Open `include/log_entry.h`.
    2. For the simple format, `LogEntry` might only need a `std::string rawMessage;` member initially. Use Copilot code completion to add this member and potentially a constructor `LogEntry(const std::string& msg) : rawMessage(msg) {}`.

### Exercise 2.2: Implement Simple `parseLine` (Edits/Completion)

* **Purpose:** Create the logic to handle one line of the simple log format.
* **Aim:** Use Copilot to generate simple parsing logic (which might just be constructing the `LogEntry`).
* **Steps:**
    1. Open `src/log_parser.cpp`.
    2. Find the skeleton for `parseLine` (it might return `std::optional<LogEntry>`).
    3. **Select the function body.**
    4. Use Copilot Edits mode or Inline Chat (`Cmd+I`):
        ```
        Implement this function. For the simple log format, it should take the input 'line', trim leading/trailing whitespace, and if the resulting line is not empty, construct and return a LogEntry object containing the trimmed line in its 'rawMessage' field. Otherwise, return std::nullopt.
        ```
    5. Review and apply the generated code. Use code completion for STL functions like `line.find_first_not_of(" \t")` etc.

### Exercise 2.3: Implement `parseLogFile` (Reading Lines) (Edits/Completion)

* **Purpose:** Implement the file reading loop.
* **Aim:** Use Copilot to generate file I/O and loop structure.
* **Steps:**
    1. Open `src/log_parser.cpp`.
    2. **Select the body** of the `parseLogFile` function.
    3. Use Copilot Edits mode or Inline Chat (`Cmd+I`):
        ```
        Implement this function. It should:
        1. Include <fstream> and <vector>.
        2. Create an std::ifstream object for the given 'filename'.
        3. Check if the file opened successfully (e.g., using `is_open()`). If not, print an error to std::cerr and return an empty std::vector<LogEntry>.
        4. Create an empty std::vector<LogEntry> to store results.
        5. Read the file line by line using std::getline.
        6. For each line read, call the 'parseLine' method.
        7. If parseLine returns a valid LogEntry (check std::optional), add it to the results vector.
        8. After the loop, return the results vector.
        ```
    4. Review and apply the generated code. Use completion to help with variable names and method calls.

### Exercise 2.4: Basic `main.cpp` Integration (Edits/Completion)

* **Purpose:** Make the main application call the parser and print basic results.
* **Aim:** Use Copilot to wire components together.
* **Steps:**
    1. Open `src/main.cpp`.
    2. Include necessary headers (`log_parser.h`, `log_reporter.h` - even if reporter is basic).
    3. Use Copilot completion or Edits mode inside `main` (after argument checking):
        ```c++
        // Placeholder - ask Copilot to help implement:
        // 1. Create a LogParser instance.
        // 2. Call parser.parseLogFile(logFilePath) to get a vector of entries.
        // 3. Create a LogReporter instance.
        // 4. Call reporter.printReport(entries) (Implement a basic printReport first).
        // 5. Include <iostream> for basic output in printReport.
        ```
    4. **Implement Basic `LogReporter::printReport`:** Open `src/log_reporter.cpp`. Select the `printReport` body. Use Edits/Ask: "Implement this method. Loop through the input vector of LogEntry objects and print the `rawMessage` of each entry to std::cout, followed by a newline." (Make sure to include `<iostream>` and `log_entry.h`).
    5. Build the project (`Cmd+Shift+P -> CMake: Build`).
    6. Run with the simple log file: `./build/log_analyzer data/simple_events.log`. Verify it prints the raw messages.

---

## Section 3: Implement Medium & Complex Parsing

**Goal:** Extend the parser and data structures to handle the `standard_app.log` and `detailed_system.log` formats.

---

### Exercise 3.1: Enhance `LogEntry` (Completion/Edits)

* **Purpose:** Add data members for timestamp, level, module, thread ID.
* **Aim:** Modify the struct/class using Copilot.
* **Steps:**
    1. Open `include/log_entry.h`.
    2. Add members corresponding to the complex format (e.g., `std::chrono::time_point timestamp;`, `LogLevel level;` (define enum `LogLevel`), `std::string module;`, `int threadId;`, `std::string messageBody;`). Use Copilot completion.
    3. Use Edits mode or Ask Copilot to update the constructor(s) to initialize these new members.

### Exercise 3.2: Refactor `parseLine` for Medium Format (Edits/Ask)

* **Purpose:** Modify the parsing logic for the 3-column format.
* **Aim:** Use Copilot to implement string splitting and basic type conversion.
* **Steps:**
    1. Open `src/log_parser.cpp`. Select the `parseLine` function body.
    2. Use Edits mode:
        ```
        Refactor this function to parse the medium log format 'YYYY-MM-DD HH:MM:SS LEVEL Message'. It should:
        1. Split the line based on spaces (potentially handling multiple spaces). Expect at least 3 parts (Date, Time, Level).
        2. Combine Date and Time, parse them into a std::chrono::time_point (you might need <sstream> and <iomanip> for std::get_time, or suggest a helper function). Store in LogEntry::timestamp.
        3. Parse the LEVEL string into the LogLevel enum (suggest creating a helper function/map for this). Store in LogEntry::level.
        4. Combine the rest of the parts into the message body string. Store in LogEntry::messageBody.
        5. Return the populated LogEntry in std::optional, or nullopt on parsing failure (e.g., bad timestamp, unknown level). Handle potential exceptions during parsing.
        ```
    3. Review, refine, and apply. You may need helper functions for timestamp and level parsing – ask Copilot to generate those too.

### Exercise 3.3: Refactor `parseLine` for Complex Format (Edits/Ask)

* **Purpose:** Further enhance parsing for the 5+ column format.
* **Aim:** Use Copilot for more complex string manipulation (finding delimiters `[]`, `()`).
* **Steps:**
    1. Open `src/log_parser.cpp`. Select the `parseLine` function body again.
    2. Use Edits mode:
        ```
        Refactor this function further to parse the complex log format 'YYYY-MM-DD HH:MM:SS.ms LEVEL [Module] (ThreadID) MessageBody'. It should:
        1. Parse Timestamp including milliseconds (update timestamp parsing logic).
        2. Parse LEVEL.
        3. Extract the Module string from within square brackets [].
        4. Extract the ThreadID integer from within parentheses (). Handle potential non-integer values.
        5. Extract the remaining MessageBody.
        6. Populate all corresponding fields in the LogEntry object.
        7. Return std::optional<LogEntry>, handling errors robustly. Use #file:README.md for format details if needed.
        ```
    3. Review, refine, and apply. This parsing is significantly harder; iterate with Copilot if needed.

### Exercise 3.4: Update `LogReporter` (Edits/Completion)

* **Purpose:** Display the newly parsed fields.
* **Aim:** Modify output formatting.
* **Steps:**
    1. Open `src/log_reporter.cpp`. Select the `printReport` method body.
    2. Use Edits/Ask: "Update this method to print the formatted timestamp, level, module, thread ID, and message body for each LogEntry, instead of just rawMessage." Use Copilot completion to access `entry.timestamp`, `entry.level`, etc. (You'll need a way to format `time_point` and `LogLevel` enum back to strings – ask Copilot to help generate helper functions if needed).
    3. Build and run with `standard_app.log` and `detailed_system.log` to verify parsing and output.

---

## Section 4: Implement Filtering & Reporting

**Goal:** Add command-line filtering capabilities and refine reporting.

---

### Exercise 4.1: Implement `LogFilter` (Edits/Completion)

* **Purpose:** Create the core filtering logic.
* **Aim:** Generate filtering code using Copilot.
* **Steps:**
    1. Open `src/log_filter.cpp`.
    2. Select the body of the `filterEntries` function (adjust signature as needed, e.g., `std::vector<LogEntry> filterEntries(const std::vector<LogEntry>& entries, const FilterCriteria& criteria)` - define `FilterCriteria` struct first).
    3. **Define `FilterCriteria`:** In `include/log_filter.h`, ask Copilot to define a simple struct `FilterCriteria` holding optional filters like `std::optional<LogLevel> levelFilter;`, `std::optional<std::string> moduleFilter;`, `std::optional<std::string> keywordFilter;`.
    4. **Implement Filtering:** Use Edits/Ask in `log_filter.cpp`:
        ```
        Implement the filterEntries function. It should take a vector of LogEntry objects and a FilterCriteria object. Return a new vector containing only the entries that match ALL specified criteria (check if optional filters have values before applying them). Filter by level, module (case-insensitive compare?), and keyword (search within messageBody, case-insensitive?). Include <vector>, <optional>, <string>, <algorithm>, <cctype>.
        ```
    5. Review and apply.

### Exercise 4.2: Implement Argument Parsing in `main.cpp` (Edits/Ask)

* **Purpose:** Allow users to specify filters via CLI arguments.
* **Aim:** Use Copilot to generate argument parsing code.
* **Steps:**
    1. Open `src/main.cpp`.
    2. Select the section inside `main` where arguments should be processed (after checking `argc`).
    3. Use Copilot Edits/Ask:
        ```
        Implement command-line argument parsing for this C++ application using a simple loop over argc/argv. Support the following options:
        --level <LEVEL_NAME> (e.g., INFO, ERROR)
        --module <ModuleName>
        --keyword <"Search Term"> (handle potential spaces if quoted)
        Store the parsed filter values into a 'FilterCriteria' object (assume this struct exists and has std::optional members). Handle basic errors like missing values for options. Include necessary headers like <string>, <vector>, <optional>.
        ```
        *(Alternative: Ask Copilot about using a simple library like `cxxopts` if you prefer, `#fetch` its documentation first)*.
    4. Review and integrate the parsing logic.

### Exercise 4.3: Integrate Filtering in `main.cpp` (Completion/Ask)

* **Purpose:** Connect parser, filter, and reporter based on CLI arguments.
* **Aim:** Use Copilot to adjust the main application flow.
* **Steps:**
    1. Open `src/main.cpp`.
    2. Modify the main flow after parsing arguments and parsing the log file:
        * Instantiate `LogFilter`.
        * Call `filter.filterEntries()` passing the parsed entries and the populated `FilterCriteria` object.
        * Pass the *result* of the filtering to `reporter.printReport()`.
    3. Use Copilot completion or ask for help wiring these components.
    4. Build and run with different filter options (e.g., `./build/log_analyzer data/detailed_system.log --level ERROR --module Database`). Verify the output is filtered correctly.

---

## Section 5: Exploration & Refinement

**Goal:** Now that a basic version exists, use Copilot to understand the code better, generate documentation, and refactor.

---

* **Exercise 5.1: Explore Symbols & Usages:** Perform **Exercises 1.6, 1.11, 1.12** (from the original list) on the code you've written.
* **Exercise 5.2: Generate Documentation:** Perform **Exercise 1.4** for key functions/classes you've implemented.
* **Exercise 5.3: Refactor Code:** Perform **Exercise 3.3** again, perhaps on a different function or asking for different refactoring goals (e.g., "improve performance", "increase readability").
* **Exercise 5.4: Understand Environment:** Perform **Exercises 1.8, 1.9, 1.10** to ask about VS Code settings or explain build/run commands you used.
* **Exercise 5.5: Fetch External Info:** Perform **Exercise 1.7** for another C++ feature you used or want to use (e.g., `std::chrono` or `std::optional`).

---

## Section 6: Ideation & Adding Features

**Goal:** Brainstorm and implement a new feature using the full Copilot workflow.

---

* **Exercise 6.1: Brainstorming:** Perform **Exercise 2.1**.
* **Exercise 6.2: Explore Idea:** Perform **Exercise 2.2** on an idea from brainstorming or Section 8.
* **Exercise 6.3: Full Feature Workflow:** Perform **Exercise 3.7** (Ideate -> Spec -> Plan -> Implement -> Refactor) for a *new* small feature not yet implemented (e.g., adding the `--stats` flag and integrating the `StatisticsCalculator` from Exercise 3.4, or implementing `--output-format CSV`).
* **Exercise 6.4: Use Custom Instructions:** Ensure `.github/copilot-instructions.md` exists (from Exercise 3.6 setup). Select a function and use Edits mode to ask Copilot to add logging or apply another guideline from the instructions file, verifying it adheres to the custom rules.
* **Exercise 6.5: Review Changes:** Perform **Exercise 3.5** after implementing a feature.

---

## Section 7: Testing & Advanced Topics

**Goal:** Focus on testing, debugging, and more advanced Copilot uses.

---

* **Exercise 7.1: Generate Test Stubs & Implement:** Perform **Exercise 3.2** again for a different function (e.g., `LogFilter::filterEntries`). Try to flesh out the asserts more thoroughly. *Challenge:* Integrate a simple test framework like Google Test using CMake (`WorkspaceContent` or find package) and adapt the generated stubs. Use Copilot to help write CMake commands for testing.
* **Exercise 7.2: Debugging Assistance:** Perform **Exercise 4.1**. Intentionally introduce a bug (if none exist!) and use Copilot to help diagnose based on error messages/debugger output.
* **Exercise 7.3: Commit Message Generation:** Perform **Exercise 4.2**.
* **Exercise 7.4: Code Review Assistance:** Perform **Exercise 4.3** on your implemented code.
* **Exercise 7.5: Exploring Alternatives:** Perform **Exercise 4.4** on a piece of your implemented C++ logic.
* **Exercise 7.6: Malformed Entry Challenge:** Perform **Exercise 4.5** using `data/malformatted_entries.log` to make your parser robust.

---

## Section 8: Next Steps & Open-Ended Challenges

**Goal:** Use the implemented features and Copilot skills as a foundation for further development. Choose one or more extensions and use Copilot to help plan and implement them.

---

This project provides a solid base. Here are some open-ended directions for further development, derived from the project's potential, where Copilot can assist in planning, generating code, writing tests, and refactoring:

* **Filtering Enhancements:**
    * Implement module filtering (`--module=ModuleName`) to filter by specific system components.
    * Implement time-based filtering (`--start-time=<YYYY-MM-DDTHH:MM:SS>`, `--end-time=<YYYY-MM-DDTHH:MM:SS>`). (Exercise 3.7 started this).
    * Add support for regular expression matching on the message body (`--regex`). (Requires including the `<regex>` header).
    * Add inclusive/exclusive filter combinations (AND/OR logic, e.g., `--filter-logic AND/OR`).
* **Output Enhancements:**
    * Enhance the default console output (`LogReporter`) to be more configurable or detailed (e.g., choose which fields to show via flags).
    * Implement new `Reporter` classes (e.g., `CsvLogReporter`, `JsonLogReporter`) using polymorphism to output in different formats (`--output-format CSV/JSON`).
    * Support output redirection to files (`--output-file <path>`).
* **Analysis Features:**
    * Implement the `StatisticsCalculator` (Exercise 3.4 started this) more fully. Add features like error counts per module, message frequency analysis, etc. Add a `--stats` flag to `main.cpp` to trigger report printing.
    * Generate summaries (e.g., total logs processed, time range covered, number of errors/warnings).
    * *(Advanced)* Visualize log patterns and trends (requires outputting data suitable for external plotting tools like Gnuplot or Python libraries).
* **Performance & Robustness:**
    * Optimize for large file handling: Modify the `LogParser` and main loop to process the file line-by-line (stream processing) instead of potentially loading everything into a `std::vector` first.
    * Improve error handling based on Exercise 4.5 results. Add more specific custom exception types derived from `std::exception`.
    * Add comprehensive unit tests using a C++ testing framework like Google Test or Catch2. Set up CMake (`CMakeLists.txt`, potentially using `WorkspaceContent` or finding installed packages) and CTest to build and run tests automatically (`make test` or `ctest` in the build directory). Use Copilot (`/tests` command) to help generate diverse test cases (happy path, edge cases, error conditions).
    * Support configuration loading from an external file (e.g., `config.ini` or `config.json`) for default filter settings or output formats, potentially using a simple parsing library.

**Challenge:** Choose one of these areas (or combine a few) and use the Copilot techniques practiced earlier (ideation, specification, planning, implementation with Edits/Ask/Completion, testing, refactoring) to extend the C++ Log Analyzer!

---

### Note on Advanced Customization: Reusable Prompt Files

(This section remains the same)

Beyond the workspace-level `.github/copilot-instructions.md` explored in Exercise 3.6, Copilot also supports **reusable prompt files**. These allow you to define more complex, multi-step prompts or instructions for specific, repeatable C++ tasks (e.g., generating a C++ class implementing RAII, adding standard error handling to a function, a detailed C++ code review checklist). You can include placeholders and combine instructions with context variables. While we haven't created a specific exercise for this, it's a powerful feature to explore if you find yourself repeatedly giving Copilot the same complex instructions for common C++ tasks within your project. Investigate the official VS Code Copilot documentation for the latest details.

---