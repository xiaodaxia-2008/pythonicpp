/**
 * Copyright © 2026 Zen Shawn. All rights reserved.
 *
 * @file string.hpp
 * @author: Zen Shawn
 * @email: xiaozisheng2008@hotmail.com
 * @date: 12:45:03, January 30, 2026
 */
#include <ranges>
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

} // namespace pythonic::str
