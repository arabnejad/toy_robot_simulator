# Toy Robot Simulator


## Build

```bash
# Configure (out-of-source)
cmake -S . -B build

# Build the RobotSim
cmake --build build --target RobotSim -- -j4
```

The `RobotSim` executable is built from `src/main.cpp`.

## Run

```bash

# Print Help
./build/RobotSim --help

# Run RobotSim with input file
./build/RobotSim --file sample_input/input1.txt

# Run RobotSim with input file with --loglevel=<level>
./build/RobotSim --file sample_input/input1.txt --loglevel=debug

# Run RobotSim with standard input
./build/RobotSim
```

## Tests

GoogleTest is fetched automatically with CMake's `FetchContent` and a small suite is compiled.

```bash
# Build tests
cmake --build build --target tests -- -j4

# Run tests
cmake --build build --target run_tests
# or directly:
ctest --test-dir build --output-on-failure
```

## Formatting

Format all sources with clang-format (if available on your PATH):

```bash
cmake --build build --target clang_format
```

## Code coverage (optional)

If you have `gcovr` installed and are using GCC or Clang, you can generate coverage reports.
Enable coverage flags at configure time:

```bash
cmake -S . -B build -DENABLE_COVERAGE=ON
```

Then generate reports:

```bash
# Console summary
cmake --build build --target gcovr_console

# HTML report in build/coverage/index.html
cmake --build build --target gcovr_html
```

## Cleaning

Remove all detectable CMake build directories under the repository (e.g., `build`, `cmake-build-*`, etc.):

```bash
cmake --build build --target clean_all
```

## Notes

- Compiler options and the C++ standard are centralized in `cmake/compiler_options.cmake`.
- clang-format settings are in `.clang-format`, and the formatting target is defined in `cmake/clang_format.cmake`.
- Coverage helpers live in `cmake/code_coverage.cmake`.

## References
  - [https://github.com/arabnejad/cpp_project_template](https://github.com/arabnejad/cpp_project_template)
  - [https://github.com/arabnejad/yamlparser/blob/master/include/YamlException.hpp](https://github.com/arabnejad/yamlparser/blob/master/include/YamlException.hpp)
  - [https://github.com/arabnejad/yamlparser/blob/master/include/YamlHelperFunctions.hpp](https://github.com/arabnejad/yamlparser/blob/master/include/YamlHelperFunctions.hpp)
  - [https://github.com/arabnejad/TaskSchedX/blob/master/include/Logger.h](https://github.com/arabnejad/TaskSchedX/blob/master/include/Logger.h)