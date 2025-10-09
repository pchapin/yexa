# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Yexa is a cross-platform terminal text editor written in C++17, inspired by the legacy "Y" editor. It's a fresh modernization of an editor originally designed for DOS in the early 1990s. The codebase is currently a light refactoring of the original Y editor and requires significant modernization work.

**Target platforms**: Linux, macOS, and Windows using GCC, clang, and MSVC
**Build system**: CMake
**Language standard**: C++17

## Building

```bash
# Standard CMake build
mkdir build
cd build
cmake ..
cmake --build .
```

The build is configured in `CMakeLists.txt` and produces the `yexa` executable.

## Architecture

### Core Design Pattern: Multiple Inheritance Hierarchy

The editor uses a sophisticated multiple inheritance pattern where functionality is composed through "mixins". The central class is `YEditFile`, which combines multiple capabilities:

```cpp
class YEditFile : public virtual EditFile,     // Base (virtual base class)
                  public BlockEditFile,         // Block operations
                  public CharacterEditFile,     // Character editing
                  public CursorEditFile,        // Cursor movement
                  public DiskEditFile,          // File I/O
                  public LineEditFile,          // Line operations
                  public SearchEditFile,        // Search/replace
                  public WPEditFile             // Word processing
```

All these classes inherit from `EditFile` as a virtual base class. This design allows mixing and matching functionality to create specialized editor file types.

### Key Components

**EditFile hierarchy** (`include/EditFile.hpp`, `src/EditFile.cpp`):
- Virtual base class containing file data (`EditList file_data`) and cursor position (`FilePosition current_point`)
- Manages block mode state and change tracking
- All editor functionality is built on top of this through the mixin pattern

**Screen library** (`screen/`):
- Self-contained library for terminal screen management
- Abstraction layer supporting multiple platforms (Windows console API, Unix curses)
- Three levels of screen access:
  1. Direct screen access (`scr` namespace functions)
  2. Simple windows (`scr::SimpleWindow` hierarchy)
  3. Managed windows with layout control (`scr::Window` + `scr::Manager`)
- Built as a static library with headers in `screen/include/screen/`
- On non-Windows platforms, requires ncurses (`find_package(Curses REQUIRED)`)

**Command system** (`include/command.hpp`, `src/command_*.cpp`):
- Each command is a separate function returning `bool` (success/failure)
- Commands organized by initial letter (e.g., `command_a.cpp`, `command_b.cpp`)
- Command dispatch through `command_table.cpp`
- Commands use global `parameter_stack` for arguments

**File management**:
- `FileList`: Global registry of all open files
- `EditList`: List of `EditBuffer` objects representing file lines
- `EditBuffer`: String-like container for text data with operations

**Macro system**:
- `macro_stack.cpp/hpp`: Macro execution stack
- `parameter_stack.cpp/hpp`: Parameter passing between commands
- Startup macro support via `ystart.ymy` file
- Macro language planned but incomplete

### Data Flow

1. `main()` in `src/yexa.cpp` initializes the editor via `global_setup()`
2. Command line arguments are pushed onto `parameter_stack`
3. `initialize()` searches for and executes `ystart.ymy` startup macro
4. Files are loaded either from command line or `filelist.yfy` session file
5. Main loop: `get_word()` → `handle_word()` → command execution

### Important Implementation Details

- **Line numbers**: 0-based internally, 1-based for user display
- **Column numbers**: 0-based internally, 1-based for user display
- **EditList**: Uses custom `List<T>` template (`include/mylist.hpp`), maintains current position pointer
- **Virtual base class quirks**: Some functions that should be virtual in `EditFile` are not, due to legacy Turbo C++ 1.0 compiler bugs (see TODOs in `EditFile.hpp:28`)

## Code Style

The project uses clang-format with the following key settings:
- Based on LLVM style
- 4-space indentation (no tabs)
- 96 character line limit
- Namespace indentation enabled
- Custom brace wrapping: functions get opening brace on new line, control statements don't
- Pointer/reference alignment to the right (`int *ptr`, `int &ref`)

Format code with: `clang-format -i <file>`

## Key File Locations

- Main entry point: `src/yexa.cpp`
- Header files: `include/`
- Screen library: `screen/` (headers in `screen/include/screen/`)
- Command implementations: `src/command_*.cpp`
- Configuration: `.clang-format` (code style)

## Development Notes

- The codebase contains legacy comments referencing "Y" - this was the original editor name
- Many TODOs exist for modernization (Unicode support, plugin system, LSP support)
- Support for DOS, OS/2, and ANSI terminals was removed; focus is on modern platforms
- The screen library documentation mentions DOS/OS/2 support in overview but this is legacy documentation
