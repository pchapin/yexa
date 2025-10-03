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
    src/BlockEditFile.cpp
    src/CharacterEditFile.cpp
    src/clipboard.cpp
    src/command_a.cpp
    src/command_b.cpp
    src/command_c.cpp
    src/command_d.cpp
    src/command_e.cpp
    src/command_f.cpp
    src/command_g.cpp
    src/command_h.cpp
    src/command_i.cpp
    src/command_k.cpp
    src/command_l.cpp
    src/command_n.cpp
    src/command_p.cpp
    src/command_q.cpp
    src/command_r.cpp
    src/command_s.cpp
    src/command_t.cpp
    src/command_table.cpp
    src/command_x.cpp
    src/command_y.cpp
    src/CursorEditFile.cpp
    src/DiskEditFile.cpp
    src/EditBuffer.cpp
    src/EditFile.cpp
    src/EditList.cpp
    src/FileList.cpp
    src/FileNameMatcher.cpp
    src/FilePosition.cpp
    src/global.cpp
    src/help.cpp
    src/keyboard.cpp
    src/LineEditFile.cpp
    src/macro_stack.cpp
    src/parameter_stack.cpp
    src/SearchEditFile.cpp
    src/special.cpp
    src/support.cpp
    src/Timer.cpp
    src/WordSource.cpp
    src/WPEditFile.cpp
    src/YEditFile.cpp
    src/yexa.cpp
    src/yfile.cpp)
target_include_directories(yexa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Linking information.
target_link_libraries(yexa PRIVATE screen)

# POSIX consoles require Curses.
if (NOT WIN32)
  find_package(Curses REQUIRED)
  target_include_directories(yexa PRIVATE ${CURSES_INCLUDE_DIR})
  target_link_libraries(yexa PRIVATE ${CURSES_LIBRARIES})
endif()