/**
 * Copyright © 2026 Zen Shawn. All rights reserved.
 *
 * @file string.hpp
 * @author: Zen Shawn
 * @email: xiaozisheng2008@hotmail.com
 * @date: 12:45:03, January 30, 2026
 */
#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <string_view>

namespace pythonic::str
{

inline auto split(std::string_view s, std::string_view delimiter = " ")
{
    return s | std::views::split(delimiter)
           | std::views::transform([](auto &&rng) {
                 return std::string_view{begin(rng), end(rng)};
             })
           | std::ranges::to<std::vector>();
}

inline auto startswith(std::string_view s, std::string_view prefix)
{
    return std::ranges::starts_with(s, prefix);
}

inline auto endswith(std::string_view s, std::string_view suffix)
{
    return std::ranges::ends_with(s, suffix);
}

inline auto lower(std::string_view s)
{
    std::string result;
    result.reserve(s.size());
    std::ranges::transform(s, std::back_inserter(result), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return result;
}

inline auto upper(std::string_view s)
{
    std::string result;
    result.reserve(s.size());
    std::ranges::transform(s, std::back_inserter(result), [](unsigned char c) {
        return static_cast<char>(std::toupper(c));
    });
    return result;
}

inline auto strip(std::string_view s, std::string_view chars = " \t\n\r\v\f")
{
    auto start = s.find_first_not_of(chars);
    if (start == std::string_view::npos) {
        return std::string_view{};
    }
    auto end = s.find_last_not_of(chars);
    return s.substr(start, end - start + 1);
}

inline auto lstrip(std::string_view s, std::string_view chars = " \t\n\r\v\f")
{
    auto start = s.find_first_not_of(chars);
    if (start == std::string_view::npos) {
        return std::string_view{};
    }
    return s.substr(start);
}

inline auto rstrip(std::string_view s, std::string_view chars = " \t\n\r\v\f")
{
    auto end = s.find_last_not_of(chars);
    if (end == std::string_view::npos) {
        return std::string_view{};
    }
    return s.substr(0, end + 1);
}

inline auto replace(std::string_view s, std::string_view old_str,
                    std::string_view new_str)
{
    if (old_str.empty()) {
        return std::string{s};
    }

    std::string result;
    result.reserve(s.size());

    size_t pos = 0;
    while (pos < s.size()) {
        size_t found = s.find(old_str, pos);
        if (found == std::string_view::npos) {
            result.append(s.substr(pos));
            break;
        }
        result.append(s.substr(pos, found - pos));
        result.append(new_str);
        pos = found + old_str.size();
    }

    return result;
}

inline auto find(std::string_view s, std::string_view sub, size_t start = 0,
                 size_t end = std::string_view::npos)
{
    if (start >= s.size()) {
        return std::string::npos;
    }
    if (end > s.size()) {
        end = s.size();
    }
    std::string_view search_area = s.substr(start, end - start);
    size_t pos = search_area.find(sub);
    return pos == std::string_view::npos ? std::string::npos : pos + start;
}

inline auto rfind(std::string_view s, std::string_view sub, size_t start = 0,
                  size_t end = std::string_view::npos)
{
    if (start >= s.size()) {
        return std::string::npos;
    }
    if (end > s.size()) {
        end = s.size();
    }
    std::string_view search_area = s.substr(start, end - start);
    size_t pos = search_area.rfind(sub);
    return pos == std::string_view::npos ? std::string::npos : pos + start;
}

inline auto count(std::string_view s, std::string_view sub, size_t start = 0,
                  size_t end = std::string_view::npos)
{
    if (sub.empty()) {
        return s.size() + 1;
    }

    if (start >= s.size()) {
        return size_t{0};
    }
    if (end > s.size()) {
        end = s.size();
    }

    size_t count = 0;
    size_t pos = start;

    while (pos < end) {
        pos = s.find(sub, pos);
        if (pos == std::string_view::npos || pos >= end) {
            break;
        }
        ++count;
        pos += sub.size();
    }

    return count;
}

inline auto capitalize(std::string_view s)
{
    if (s.empty()) {
        return std::string{};
    }

    std::string result;
    result.reserve(s.size());
    result.push_back(
        static_cast<char>(std::toupper(static_cast<unsigned char>(s[0]))));

    if (s.size() > 1) {
        std::ranges::transform(
            s.substr(1), std::back_inserter(result),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    }

    return result;
}

inline auto swapcase(std::string_view s)
{
    std::string result;
    result.reserve(s.size());
    std::ranges::transform(s, std::back_inserter(result), [](unsigned char c) {
        if (std::isupper(c)) {
            return static_cast<char>(std::tolower(c));
        }
        else if (std::islower(c)) {
            return static_cast<char>(std::toupper(c));
        }
        return static_cast<char>(c);
    });
    return result;
}

inline auto title(std::string_view s)
{
    std::string result;
    result.reserve(s.size());

    bool new_word = true;
    for (unsigned char c : s) {
        if (std::isspace(c)) {
            result.push_back(static_cast<char>(c));
            new_word = true;
        }
        else if (new_word) {
            result.push_back(static_cast<char>(std::toupper(c)));
            new_word = false;
        }
        else {
            result.push_back(static_cast<char>(std::tolower(c)));
        }
    }

    return result;
}

inline auto islower(std::string_view s)
{
    if (s.empty()) {
        return false;
    }

    bool has_cased = false;
    for (unsigned char c : s) {
        if (std::isalpha(c)) {
            has_cased = true;
            if (!std::islower(c)) {
                return false;
            }
        }
    }

    return has_cased;
}

inline auto isupper(std::string_view s)
{
    if (s.empty()) {
        return false;
    }

    bool has_cased = false;
    for (unsigned char c : s) {
        if (std::isalpha(c)) {
            has_cased = true;
            if (!std::isupper(c)) {
                return false;
            }
        }
    }

    return has_cased;
}

inline auto isspace(std::string_view s)
{
    if (s.empty()) {
        return false;
    }

    for (unsigned char c : s) {
        if (!std::isspace(c)) {
            return false;
        }
    }

    return true;
}

inline auto isalpha(std::string_view s)
{
    if (s.empty()) {
        return false;
    }

    for (unsigned char c : s) {
        if (!std::isalpha(c)) {
            return false;
        }
    }

    return true;
}

inline auto isdigit(std::string_view s)
{
    if (s.empty()) {
        return false;
    }

    for (unsigned char c : s) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}

inline auto isalnum(std::string_view s)
{
    if (s.empty()) {
        return false;
    }

    for (unsigned char c : s) {
        if (!std::isalnum(c)) {
            return false;
        }
    }

    return true;
}

inline auto join(const std::vector<std::string_view> &parts,
                 std::string_view separator = "")
{
    if (parts.empty()) {
        return std::string{};
    }

    size_t total_size = 0;
    for (const auto &part : parts) {
        total_size += part.size();
    }
    total_size += separator.size() * (parts.size() - 1);

    std::string result;
    result.reserve(total_size);

    bool first = true;
    for (const auto &part : parts) {
        if (!first) {
            result.append(separator);
        }
        result.append(part);
        first = false;
    }

    return result;
}

inline auto removeprefix(std::string_view s, std::string_view prefix)
    -> std::string
{
    if (s.starts_with(prefix)) {
        return std::string{s.substr(prefix.size())};
    }
    return std::string{s};
}

inline auto removesuffix(std::string_view s, std::string_view suffix)
    -> std::string
{
    if (s.ends_with(suffix)) {
        return std::string{s.substr(0, s.size() - suffix.size())};
    }
    return std::string{s};
}

inline auto splitlines(std::string_view s, bool keepends = false)
{
    std::vector<std::string> result;

    size_t start = 0;
    while (start < s.size()) {
        size_t end = s.find_first_of("\n\r", start);

        if (end == std::string_view::npos) {
            result.emplace_back(s.substr(start));
            break;
        }

        std::string_view line
            = s.substr(start, end - start + (keepends ? 1 : 0));
        result.emplace_back(line);

        // Handle \r\n
        if (s[end] == '\r' && end + 1 < s.size() && s[end + 1] == '\n') {
            if (keepends) {
                result.back().push_back('\n');
            }
            start = end + 2;
        }
        else {
            start = end + 1;
        }
    }

    return result;
}

} // namespace pythonic::str
