

# MiniProcExplore

A small/minimal process explorer written in C++ for inspecting running processes and basic process information. This repository contains the source file MiniProcExplorer.cpp and a minimal implementation to enumerate and display process details.

## Features
- Enumerates running processes
- Displays process ID (PID) and basic process information
- Lightweight, single-file implementation (MiniProcExplorer.cpp)
- Intended as a learning/example project or a small diagnostic utility

## Requirements
- C++ compiler supporting C++11 or later (C++17 recommended)
- On Windows: Visual Studio (MSVC) or MinGW

## Build
General compile commands:

- Using MinGW (Windows):
  g++ MiniProcExplorer.cpp -o MiniProcExplorer.exe

- Using Visual Studio (MSVC):
  Open Developer Command Prompt and run:
  cl /EHsc /std:c++17 MiniProcExplorer.cpp /Fe:MiniProcExplorer.exe

If the source uses platform-specific headers (e.g., <windows.h>), compile on the corresponding platform and add any required libraries.

## Usage
Run the compiled binary from the command line:

- Windows:
  MiniProcExplorer.exe

## Contributing
Contributions are welcome. Suggested steps:
1. Fork the repository.
2. Create a feature branch: git checkout -b feat-descriptive-name
3. Make changes and add tests/documentation where appropriate.
4. Open a pull request describing your changes.

Please open an issue or discussion before implementing large features.

## TODO / Roadmap
- Detect and display additional process details (memory, threads, start time)
- Add command-line filters (by name, PID)
- Add cross-platform support (conditional compilation)
- Add GUI front-end (optional)

## Contact / Author
Repository: narjesia-zey/MiniProcExplore  
Author: narjesia-zey

---