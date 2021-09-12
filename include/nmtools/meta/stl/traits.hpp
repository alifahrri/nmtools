#ifndef NMTOOLS_META_STL_TRAITS_HPP
#define NMTOOLS_META_STL_TRAITS_HPP

#include "nmtools/meta/traits.hpp"

#include <optional>

namespace nmtools::meta
{
    // std::nullopt is nothing type
    template <>
    struct is_nothing<::std::nullopt_t> : std::true_type {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRAITS_HPP