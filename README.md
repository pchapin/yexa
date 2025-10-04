
Yexa
====

Yexa is a cross-platform text editor for the terminal.

## Overview

Yexa is inspired by an older editor called "Y" written by Peter Chapin to support computer
engineering students at what was then Vermont Technical College (now Vermont State University).
Y was designed in the early 1990s to run on DOS systems and was widely used in that environment
for many years. Y was later ported to Windows, OS/2, and Linux. A significant update to Y was
started that added support for a macro language and other features, but that work was never
completed.

Yexa is a fresh start on the original Y editor. It is written in C++ 17, and uses modern build
systems, tools, libraries, and best practices. It is also more ambitious. Yexa aims to support
Unicode and to be more extensible than the original Y via an as-yet-to-be-defined plugin system.
The Language Server Protocol (LSP) will also be supported. The macro language planned for the
original Y will be part of Yexa's feature set, but support for a Lua-based macro language is
planned as well.

The Yexa codebase is currently a light refactoring of the incomplete Y update mentioned above.
Much work needs to be done to modernize the code and to position the codebase for future growth.
Although Y supported DOS and OS/2, that support required the use of Open Watcom C++.
Unfortunately, Open Watcom only implements C++ 1998, which is too old to satisfy Yexa's priority
of using modern C++ features and best practices. Yexa targets Linux, macOS, and Windows using
GCC, clang, and MSVC.

## Tooling

Yexa uses CMake as its build system. Visual Studio (Windows), Visual Studio Code, and CLion
(cross-platform) are supported IDEs, but other editors will likely also work well (Emacs,
Neovim, Sublime, Helix, etc.).

TODO: Add additional information about how to set up a development environment.

## Building Yexa

To build Yexa using CMake, execute the following commands:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
``` 

This should work on all supported platforms. Any IDE that understands CMake should also be able
to build the project.

Peter Chapin  
spicacality@kelseymountain.org  
