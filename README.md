# Project README

## Overview
The project is a cellular automaton simulation program implemented in C. It uses a graphical interface to display the state of the automaton and allows for basic control through keyboard input.

## Features
- **Cellular Automaton Simulation**: The core functionality is to simulate a cellular automaton with a 2D grid where each cell can be either active or inactive.
- **Graphical Interface**: Uses a library to render the grid and cells on a window.
- **Keyboard Controls**: Basic controls for pausing, stepping, and resetting the simulation.
- **Build & Run Across Multiple Platforms**: Supports building and running on Linux, Windows, Wine, and WebAssembly (emscripten).

## Project Structure
```
<project>/
├── build/                  # Compiled executable files
├── src/                    # Source code
│   ├── Main.c              # Entry point of the program
│   ├── cellular.h          # Header file for cellular automaton functions
│   └── window.h            # Header file for graphical interface functions
├── Makefile.linux          # Build configuration for Linux
├── Makefile.windows        # Build configuration for Windows
├── Makefile.wine           # Build configuration for Wine
└── Makefile.web            # Build configuration for WebAssembly
```

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed:
  - X11 for Linux graphical interface
  - Win32 API for Windows graphical interface
  - emscripten for WebAssembly

## Build & Run
### Linux
To build the project on Linux:
```sh
cd <project>
make -f Makefile.linux all
```

To run the compiled executable:
```sh
make -f Makefile.linux exe
```

### Windows
To build the project on Windows:
```sh
cd <project>
make -f Makefile.windows all
```

To run the compiled executable:
```sh
make -f Makefile.windows exe
```

### Wine (Linux cross compile for Windows)
To build the project using Wine on Linux:
```sh
cd <project>
make -f Makefile.wine all
```

To run the compiled executable:
```sh
make -f Makefile.wine exe
```

### WebAssembly (emscripten)
To build the project as a WebAssembly module:
```sh
cd <project>
make -f Makefile.web all
```

To serve and run the WebAssembly module:
```sh
make -f Makefile.web exe
```

These makefiles provide a straightforward way to compile and run the project on different platforms, ensuring compatibility across Linux, Windows, and WebAssembly environments.