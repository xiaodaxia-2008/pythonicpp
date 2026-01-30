#AGENTS.md - Pythonicpp Development Guide

## Project Overview
Pythonicpp is a C++ library that provides Python-like utilities for C++ development. The project uses CMake for building, Catch2 for testing, and follows modern C++23 standards.

## Build System

### Prerequisites
- CMake 3.25 or higher
- C++23 compatible compiler (GCC 13+, Clang 16+, MSVC 2022+)
- Ninja (recommended) or Make

### Build Commands

```bash
#Configure and build from scratch
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel

#Debug build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --parallel

#Build with tests enabled(default)
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DPYTHONICPP_BUILD_TEST=ON ..
cmake --build . --parallel

#Build without tests
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DPYTHONICPP_BUILD_TEST=OFF ..
cmake --build . --parallel
```

### Running Tests

```bash
#Run all tests
cd build
ctest --output-on-failure

#Run specific test by name
ctest -R "String" --output-on-failure

#Run tests with verbose output
ctest -V

#Run test executable directly
./bin/test_pythonicpp

#Run single test case
./bin/test_pythonicpp "[split]"

#List all available tests
./bin/test_pythonicpp --list-tests
```

### Linting and Formatting

```bash
#Format code with clang - format
clang-format -i include/pythonicpp/*.hpp test/*.cpp

# Check formatting without applying
clang-format --dry-run -Werror include/pythonicpp/*.hpp test/*.cpp

# Run clang-tidy static analysis
cd build
clang-tidy -p . ../include/pythonicpp/*.hpp ../test/*.cpp

# Run clang-tidy with fixes
clang-tidy -p . ../include/pythonicpp/*.hpp ../test/*.cpp --fix
```

## Code Style Guidelines

### General Principles
- Follow modern C++23 best practices
- Use Python-inspired APIs where appropriate
- Prefer simplicity and readability over micro-optimizations
- Header-only library design

### Naming Conventions
- **Namespaces**: `pythonic::str` (lowercase, descriptive)
- **Functions**: `split`, `endswith` (lowercase, snake_case for Python-like functions)
- **Variables**: `std::string_view s` (descriptive, lowercase snake_case)
- **Types**: Use standard library types (`std::string_view`, `std::vector`)
- **Macros**: UPPER_CASE (only for test macros like `TEST_CASE`)

### File Organization
- **Headers**: `include/pythonicpp/<module>.hpp`
- **Tests**: `test/test_<module>.cpp`
- One header file per module/feature
- Tests mirror header structure

### Import/Include Order
1. System headers (`<catch2/catch_test_macros.hpp>`)
2. Library headers (`<pythonicpp/string.hpp>`)
3. Group related includes together
4. Alphabetical order within groups

Example:
```cpp
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <pythonicpp/string.hpp>
```

### Formatting Rules
- **Indentation**: 4 spaces (no tabs)
- **Line length**: No hard limit, but prefer readability
- **Braces**: K&R style with opening brace on same line
- **Automatic braces**: Enabled for control statements
- **Pointer alignment**: Right (`Type* ptr`)
- **Access modifiers**: Indented -4 spaces

See `.clang-format` for complete formatting rules.

### Type Usage
- Prefer `std::string_view` over `const std::string&` for read-only string parameters
- Use `auto` when type is obvious from context
- Return views (`std::string_view`) when possible to avoid copies
- Use `constexpr` and `consteval` where appropriate
- Leverage C++23 features like `std::ranges`

### Error Handling
- Use exceptions for unexpected errors
- Return `bool` or `std::optional` for expected failures
- Document preconditions and postconditions
- Use `assert()` for internal invariants in debug builds

### Testing Guidelines
- Use Catch2 test framework
- Test file naming: `test_<module>.cpp`
- Test case naming: Descriptive names in quotes
- Use tags for test organization: `[split]`, `[endswith]`
- Include both positive and negative test cases
- Test edge cases and boundary conditions

Example test structure:
```cpp
TEST_CASE("String", "[split]")
{
    // Test code
}

TEST_CASE("String endswith", "[endswith]")
{
    // Test code
}
```

### Documentation
- Header comments with copyright and author information
- Doxygen-style comments for public APIs
- Brief function descriptions
- Parameter and return value documentation
- Example usage in comments

### Performance Considerations
- Prefer compile-time computations where possible
- Use `std::string_view` to avoid allocations
- Leverage `std::ranges` for lazy evaluation
- Consider `constexpr` evaluation
- Profile before optimizing

## Development Workflow

1. **Create feature branch**: `git checkout -b feature/name`
2. **Implement changes**: Follow code style guidelines
3. **Add tests**: Create or update test files
4. **Run tests**: `cd build && ctest --output-on-failure`
5. **Format code**: `clang-format -i include/pythonicpp/*.hpp test/*.cpp`
6. **Static analysis**: `clang-tidy -p . ../include/pythonicpp/*.hpp ../test/*.cpp`
7. **Commit changes**: Descriptive commit messages
8. **Create PR**: Include test results and rationale

## Common Tasks

### Adding New String Utility
1. Add function to `include/pythonicpp/string.hpp`
2. Implement using modern C++23 features
3. Add tests to `test/test_string.cpp`
4. Update README.md with usage examples

#### Currently Implemented String Methods (25):
- **Case Conversion**: `lower`, `upper`, `capitalize`, `swapcase`, `title`
- **Search and Find**: `find`, `rfind`, `count`, `startswith`, `endswith`
- **Trimming and Stripping**: `strip`, `lstrip`, `rstrip`, `removeprefix`, `removesuffix`
- **Splitting and Joining**: `split`, `splitlines`, `join`
- **Replacement**: `replace`
- **Validation**: `islower`, `isupper`, `isspace`, `isalpha`, `isdigit`, `isalnum`

#### Python Methods Not Yet Implemented:
- `casefold()`, `center()`, `encode()`, `expandtabs()`, `format()`, `format_map()`
- `index()`, `rindex()`, `isascii()`, `isdecimal()`, `isidentifier()`, `isnumeric()`
- `isprintable()`, `istitle()`, `ljust()`, `rjust()`, `maketrans()`, `partition()`
- `rpartition()`, `rsplit()`, `translate()`, `zfill()`

### Running Single Test
```bash
cd build
./bin/test_pythonicpp "[test_tag]"
```

### Debugging Tests
```bash
cd build
gdb ./bin/test_pythonicpp
# or
lldb ./bin/test_pythonicpp
```

### Generating Documentation
```bash
# Install Doxygen first
doxygen Doxyfile
```

## Project Structure
```
pythonicpp/
├── include/pythonicpp/     # Public headers
│   └── string.hpp          # String utilities
├── test/                   # Test files
│   ├── CMakeLists.txt      # Test configuration
│   └── test_string.cpp     # String tests
├── build/                  # Build directory
├── CMakeLists.txt          # Root CMake configuration
├── .clang-format           # Code formatting rules
├── .clang-tidy             # Static analysis rules
└── README.md               # Project documentation
```

## Dependencies
- **Catch2 v3.12.0**: Testing framework (fetched automatically)
- **C++ Standard Library**: C++23 features required

## Continuous Integration
- Build with multiple compilers (GCC, Clang, MSVC)
- Run all tests on each commit
- Enforce code formatting with clang-format
- Static analysis with clang-tidy
- No runtime dependencies beyond standard library