#ifndef NMTOOLS_META_STL_TRANSFORM_HPP
#define NMTOOLS_META_STL_TRANSFORM_HPP

#include "nmtools/meta/transform.hpp"

#include <optional>

namespace nmtools::meta
{

#ifndef NMTOOLS_META_MAKE_MAYBE_TYPE
#define NMTOOLS_META_MAKE_MAYBE_TYPE
    template <typename T, typename>
    struct make_maybe_type
    {
        using type = std::optional<T>;
    }; // make_maybe_type

    template <typename T>
    using make_maybe_type_t = type_t<make_maybe_type<T>>;

    template <typename>
    struct make_nothing
    {
        using type = std::nullopt_t;
    }; // make_nothing

    template <typename T=void>
    using make_nothing_t = type_t<make_nothing<T>>;
#endif // NMTOOLS_META_MAKE_MAYBE_TYPE

    // TODO: add make_tuple, make_either...
} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRANSFORM_HPP