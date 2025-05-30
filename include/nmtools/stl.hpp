#ifndef NMTOOLS_STL_HPP
#define NMTOOLS_STL_HPP

#include "nmtools/platform.hpp"

#ifndef NMTOOLS_DISABLE_STL

#if __has_include(<array>)
// if exists, assume the other also exists
#include <array>
#include <tuple>
#include <variant>
#include <optional>

#ifndef nmtools_either
#define nmtools_either ::std::variant
#endif // nmtools_either

#ifndef nmtools_tuple
#define nmtools_tuple ::std::tuple
#endif // nmtools_tuple

#ifndef nmtools_maybe
#define nmtools_maybe   ::std::optional
#define nmtools_nothing ::std::nullopt
#endif // nmtools_maybe

#ifndef nmtools_array
#define nmtools_array ::std::array
#endif // nmtools_array

#if __has_include(<vector>)
#include <vector>

#ifndef nmtools_list
#define nmtools_list ::std::vector
#endif
#endif // __has_include(<vector>)

#include <stack>
#include <queue>

// TODO: fix for std
// #ifndef nmtools_queue
// #define nmtools_queue ::std::queue
// #endif // nmtools_queue

// #ifndef nmtools_stack
// #define nmtools_stack ::std::stack
// #endif // nmtools_stack

#endif // __has_include(<array>)

#endif // NMTOOLS_DISABLE_STL

// utl provides stl-like interface limited to nmtools usage
#include "nmtools/utl.hpp"

namespace nmtools::meta
{
    constexpr inline auto Nothing = nmtools_nothing;
}

#endif // NMTOOLS_STL_HPP