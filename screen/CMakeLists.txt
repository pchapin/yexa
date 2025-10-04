# Define screen library
add_library(screen STATIC
    src/CommandWindow.cpp
    src/debug.cpp
    src/DisplayWindow.cpp
    src/ImageBuffer.cpp
    src/InputWindow.cpp
    src/key.cpp
    src/ListWindow.cpp
    src/Manager.cpp
    src/MessageWindow.cpp
    src/scr.cpp
    src/screen.cpp
    src/scrtools.cpp
    src/SelectWindow.cpp
    src/Shadow.cpp
    src/StatusLine.cpp
    src/TextWindow.cpp
    src/Window.cpp)

# Public headers go here
target_include_directories(screen PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# You can add compile options or definitions here if needed
# target_compile_definitions(screen PRIVATE ...)
