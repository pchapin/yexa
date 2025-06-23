cmake_minimum_required(VERSION 3.16)
project(yexa LANGUAGES CXX)

# Set C++ standard (adjust as needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the screen library subdirectory
add_subdirectory(screen)

# Main executable
add_executable(yexa
    src/main.cpp
)

# Link screen library
target_link_libraries(yexa PRIVATE screen)

# Optional: include top-level include dirs (if needed later)
# target_include_directories(yexa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
