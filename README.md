#Pythonicpp

Use C++ in a Pythonic way - a header-only C++23 library providing Python-like string utilities.

## Features

- **Modern C++23**: Uses `std::ranges`, `std::string_view`, and other C++23 features
- **Header-only**: Easy to integrate into any project
- **Python-like API**: Familiar syntax for Python developers
- **Efficient**: Returns views where possible to avoid copies
- **Comprehensive**: 25+ Python string methods implemented

## Installation

```bash
#Clone the repository
git clone https://github.com/yourusername/pythonicpp.git
cd pythonicpp

#Build and test
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel
ctest --output-on-failure
```

## Quick Start

```c++
#include <pythonicpp/string.hpp>

using namespace pythonic;

int main()
{
    std::string s = "  Hello World!  ";

    // Python-like string operations
    auto trimmed = str::strip(s);         // "Hello World!"
    auto lower = str::lower(s);           // "  hello world!  "
    auto words = str::split(trimmed);     // ["Hello", "World!"]
    auto joined = str::join(words, ", "); // "Hello, World!"

    return 0;
}
```

## String Methods Reference

### Case Conversion
- `str::lower(s)` - Convert to lowercase - `str::upper(s)`
- Convert to uppercase - `str::capitalize(s)` - Capitalize first character
- `str::swapcase(s)` - Swap case of characters - `str::title(s)`
- Title case the string

### Search and Find
- `str::find(s, sub, start = 0, end = npos)` - Find first occurrence
- `str::rfind(s, sub, start = 0, end = npos)` - Find last occurrence
- `str::count(s, sub, start = 0, end = npos)` - Count occurrences
- `str::startswith(s, prefix)` - Check if starts with prefix
- `str::endswith(s, suffix)`
- Check if ends with suffix

### Trimming and Stripping
- `str::strip(s, chars = " \t\n\r\v\f")` - Strip leading / trailing chars
- `str::lstrip(s, chars = " \t\n\r\v\f")` - Strip leading chars
- `str::rstrip(s, chars = " \t\n\r\v\f")` - Strip trailing chars
- `str::removeprefix(s, prefix)` - Remove prefix if present
- `str::removesuffix(s, suffix)`
- Remove suffix if present

### Splitting and Joining
- `str::split(s, delimiter = " ")` - Split by delimiter
- `str::splitlines(s, keepends = false)` - Split by line boundaries
- `str::join(parts, separator = "")`
- Join strings with separator

### Replacement
- `str::replace(s, old_str, new_str)`
- Replace all occurrences

### Validation
- `str::islower(s)` - Check if all cased chars are lowercase
- `str::isupper(s)` - Check if all cased chars are uppercase
- `str::isspace(s)` - Check if all chars are whitespace - `str::isalpha(s)`
- Check if all chars are alphabetic - `str::isdigit(s)`
- Check if all chars are digits - `str::isalnum(s)`
- Check if all chars are alphanumeric

## License

MIT License - see LICENSE file for details.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Implement changes with tests
4. Format code with clang-format
5. Submit a pull request
