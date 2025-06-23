# Define screen library
add_library(screen STATIC
    src/screen.cpp
)

# Public headers go here
target_include_directories(screen PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# You can add compile options or definitions here if needed
# target_compile_definitions(screen PRIVATE ...)
