# Pythonicpp

Use c++ in pythonic way.


# Usage

- string utilities:

```c++
#include <pythonicpp/string.hpp>

using namespace pythonicpp;

int main() {
    std::string s = "hello world !";

    // string split
    std::vector<std::string_view> tokens = str::split(s, " "); // ["hello", "world", "!"]
}
```