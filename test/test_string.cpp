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

TEST_CASE("String endswith", "[endswith]")
{
    std::string_view s = "hello world";

    REQUIRE(str::endswith(s, "world") == true);
    REQUIRE(str::endswith(s, "hello") == false);
    REQUIRE(str::endswith(s, "world!") == false);
    REQUIRE(str::endswith(s, "") == true);
}

TEST_CASE("String startswith", "[startswith]")
{
    std::string_view s = "hello world";

    REQUIRE(str::startswith(s, "hello") == true);
    REQUIRE(str::startswith(s, "world") == false);
    REQUIRE(str::startswith(s, "hello!") == false);
    REQUIRE(str::startswith(s, "") == true);
}

TEST_CASE("String case conversion", "[case]")
{
    SECTION("lower")
    {
        REQUIRE(str::lower("Hello World") == "hello world");
        REQUIRE(str::lower("HELLO") == "hello");
        REQUIRE(str::lower("hello") == "hello");
        REQUIRE(str::lower("123") == "123");
        REQUIRE(str::lower("") == "");
    }

    SECTION("upper")
    {
        REQUIRE(str::upper("Hello World") == "HELLO WORLD");
        REQUIRE(str::upper("hello") == "HELLO");
        REQUIRE(str::upper("HELLO") == "HELLO");
        REQUIRE(str::upper("123") == "123");
        REQUIRE(str::upper("") == "");
    }

    SECTION("capitalize")
    {
        REQUIRE(str::capitalize("hello world") == "Hello world");
        REQUIRE(str::capitalize("HELLO") == "Hello");
        REQUIRE(str::capitalize("123abc") == "123abc");
        REQUIRE(str::capitalize("") == "");
        REQUIRE(str::capitalize("a") == "A");
    }

    SECTION("swapcase")
    {
        REQUIRE(str::swapcase("Hello World") == "hELLO wORLD");
        REQUIRE(str::swapcase("HELLO") == "hello");
        REQUIRE(str::swapcase("hello") == "HELLO");
        REQUIRE(str::swapcase("123") == "123");
        REQUIRE(str::swapcase("") == "");
    }

    SECTION("title")
    {
        REQUIRE(str::title("hello world") == "Hello World");
        REQUIRE(str::title("HELLO WORLD") == "Hello World");
        REQUIRE(str::title("hello   world") == "Hello   World");
        REQUIRE(str::title("123 abc") == "123 Abc");
        REQUIRE(str::title("") == "");
    }
}

TEST_CASE("String stripping", "[strip]")
{
    std::string_view s = "  hello world  ";
    std::string_view s2 = "\t\nhello world\r\n";
    std::string_view s3 = "xxhelloxx";

    SECTION("strip")
    {
        REQUIRE(str::strip(s) == "hello world");
        REQUIRE(str::strip(s2) == "hello world");
        REQUIRE(str::strip(s3, "x") == "hello");
        REQUIRE(str::strip("") == "");
        REQUIRE(str::strip("   ") == "");
    }

    SECTION("lstrip")
    {
        REQUIRE(str::lstrip(s) == "hello world  ");
        REQUIRE(str::lstrip(s2) == "hello world\r\n");
        REQUIRE(str::lstrip(s3, "x") == "helloxx");
        REQUIRE(str::lstrip("") == "");
        REQUIRE(str::lstrip("   ") == "");
    }

    SECTION("rstrip")
    {
        REQUIRE(str::rstrip(s) == "  hello world");
        REQUIRE(str::rstrip(s2) == "\t\nhello world");
        REQUIRE(str::rstrip(s3, "x") == "xxhello");
        REQUIRE(str::rstrip("") == "");
        REQUIRE(str::rstrip("   ") == "");
    }
}

TEST_CASE("String replace", "[replace]")
{
    SECTION("basic replace")
    {
        REQUIRE(str::replace("hello world", "world", "there") == "hello there");
        REQUIRE(str::replace("hello world world", "world", "there")
                == "hello there there");
        REQUIRE(str::replace("hello", "x", "y") == "hello");
        REQUIRE(str::replace("", "x", "y") == "");
        REQUIRE(str::replace("hello", "", "x") == "hello");
    }

    SECTION("empty string replace")
    {
        REQUIRE(str::replace("hello", "hello", "") == "");
        REQUIRE(str::replace("hellohello", "hello", "") == "");
    }
}

TEST_CASE("String search", "[search]")
{
    std::string_view s = "hello world hello";

    SECTION("find")
    {
        REQUIRE(str::find(s, "world") == 6);
        REQUIRE(str::find(s, "hello") == 0);
        REQUIRE(str::find(s, "x") == std::string::npos);
        REQUIRE(str::find(s, "hello", 1) == 12);
        REQUIRE(str::find(s, "hello", 1, 10) == std::string::npos);
        REQUIRE(str::find("", "x") == std::string::npos);
        REQUIRE(str::find("hello", "") == 0);
    }

    SECTION("rfind")
    {
        REQUIRE(str::rfind(s, "world") == 6);
        REQUIRE(str::rfind(s, "hello") == 12);
        REQUIRE(str::rfind(s, "x") == std::string::npos);
        REQUIRE(str::rfind(s, "hello", 0, 10) == 0);
        REQUIRE(str::rfind("", "x") == std::string::npos);
        REQUIRE(str::rfind("hello", "") == 5);
    }

    SECTION("count")
    {
        REQUIRE(str::count(s, "hello") == 2);
        REQUIRE(str::count(s, "world") == 1);
        REQUIRE(str::count(s, "x") == 0);
        REQUIRE(str::count(s, "hello", 1) == 1);
        REQUIRE(str::count(s, "hello", 0, 10) == 1);
        REQUIRE(str::count("", "x") == 0);
        REQUIRE(str::count("hello", "") == 6);
        REQUIRE(str::count("aaaa", "aa") == 2);
    }
}

TEST_CASE("String validation", "[validation]")
{
    SECTION("islower")
    {
        REQUIRE(str::islower("hello") == true);
        REQUIRE(str::islower("Hello") == false);
        REQUIRE(str::islower("HELLO") == false);
        REQUIRE(str::islower("123") == false);
        REQUIRE(str::islower("") == false);
        REQUIRE(str::islower("hello123") == true);
    }

    SECTION("isupper")
    {
        REQUIRE(str::isupper("HELLO") == true);
        REQUIRE(str::isupper("Hello") == false);
        REQUIRE(str::isupper("hello") == false);
        REQUIRE(str::isupper("123") == false);
        REQUIRE(str::isupper("") == false);
        REQUIRE(str::isupper("HELLO123") == true);
    }

    SECTION("isspace")
    {
        REQUIRE(str::isspace("   ") == true);
        REQUIRE(str::isspace("\t\n ") == true);
        REQUIRE(str::isspace("hello") == false);
        REQUIRE(str::isspace("") == false);
        REQUIRE(str::isspace("  hello  ") == false);
    }

    SECTION("isalpha")
    {
        REQUIRE(str::isalpha("hello") == true);
        REQUIRE(str::isalpha("HELLO") == true);
        REQUIRE(str::isalpha("hello123") == false);
        REQUIRE(str::isalpha("") == false);
        REQUIRE(str::isalpha(" ") == false);
    }

    SECTION("isdigit")
    {
        REQUIRE(str::isdigit("123") == true);
        REQUIRE(str::isdigit("123abc") == false);
        REQUIRE(str::isdigit("") == false);
        REQUIRE(str::isdigit(" ") == false);
        REQUIRE(str::isdigit("12.3") == false);
    }

    SECTION("isalnum")
    {
        REQUIRE(str::isalnum("hello123") == true);
        REQUIRE(str::isalnum("HELLO") == true);
        REQUIRE(str::isalnum("123") == true);
        REQUIRE(str::isalnum("hello 123") == false);
        REQUIRE(str::isalnum("") == false);
        REQUIRE(str::isalnum("hello!") == false);
    }
}

TEST_CASE("String join and splitlines", "[join_splitlines]")
{
    SECTION("join")
    {
        std::vector<std::string_view> parts = {"hello", "world", "test"};
        REQUIRE(str::join(parts, ", ") == "hello, world, test");
        REQUIRE(str::join(parts, "") == "helloworldtest");
        REQUIRE(str::join({}, ", ") == "");
        REQUIRE(str::join({"single"}, ", ") == "single");
    }

    SECTION("removeprefix")
    {
        REQUIRE(str::removeprefix("hello world", "hello ") == "world");
        REQUIRE(str::removeprefix("hello world", "world") == "hello world");
        REQUIRE(str::removeprefix("hello", "") == "hello");
        REQUIRE(str::removeprefix("", "hello") == "");
    }

    SECTION("removesuffix")
    {
        REQUIRE(str::removesuffix("hello world", " world") == "hello");
        REQUIRE(str::removesuffix("hello world", "hello") == "hello world");
        REQUIRE(str::removesuffix("hello", "") == "hello");
        REQUIRE(str::removesuffix("", "world") == "");
    }

    SECTION("splitlines")
    {
        auto lines1 = str::splitlines("hello\nworld\n");
        REQUIRE(lines1.size() == 2);
        REQUIRE(lines1[0] == "hello");
        REQUIRE(lines1[1] == "world");

        auto lines2 = str::splitlines("hello\r\nworld\r\n", true);
        REQUIRE(lines2.size() == 2);
        REQUIRE(lines2[0] == "hello\r\n");
        REQUIRE(lines2[1] == "world\r\n");

        auto lines3 = str::splitlines("hello\n\nworld");
        REQUIRE(lines3.size() == 3);
        REQUIRE(lines3[0] == "hello");
        REQUIRE(lines3[1] == "");
        REQUIRE(lines3[2] == "world");

        auto lines4 = str::splitlines("");
        REQUIRE(lines4.size() == 0);
    }
}