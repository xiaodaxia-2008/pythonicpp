#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <pythonicpp/string.hpp>

using namespace pythonic;

TEST_CASE("String", "[split]")
{
    std::string_view s = "hello world !";

    std::vector<std::string_view> tokens = str::split(s);

    std::vector<std::string_view> expected = {"hello", "world", "!"};

    REQUIRE_THAT(tokens, Catch::Matchers::Equals(expected));
}