#ifndef NMTOOLS_STL_HPP
#define NMTOOLS_STL_HPP

#ifndef NMTOOLS_DISABLE_STL

#if __has_include(<array>)
// if exists, assume the other also exists
#include <array>
#include <tuple>
#include <variant>
#include <optional>
#endif

#if __has_include(<vector>)
#include <vector>
#endif

#ifndef nmtools_list
#define nmtools_list ::std::vector
#endif

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

#endif // NMTOOLS_DISABLE_STL

// utl provides stl-like interface limited to nmtools usage
#include "nmtools/utl.hpp"

namespace nmtools::meta
{
    constexpr inline auto Nothing = nmtools_nothing;
}

#endif // NMTOOLS_STL_HPP