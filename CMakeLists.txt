# CMakeLists.txt (in log-analyzer root)

cmake_minimum_required(VERSION 3.15) # Require CMake version 3.15 or higher
project(LogAnalyzer VERSION 1.0 LANGUAGES CXX) # Project name, version, language (C++)

# Set C++ standard (e.g., C++17 or C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Avoid compiler-specific extensions

# Add the executable target, linking main.cpp initially
# We will add more source files later
add_executable(log_analyzer src/main.cpp)

# Tell the target where to find header files (#include <...>)
# Targets the 'include' directory we created
target_include_directories(log_analyzer PUBLIC include)

# --- Add other source files, libraries, etc. below later ---