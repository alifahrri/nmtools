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

    // std::nullopt_t has no default constructor
    inline constexpr auto nothing = ::std::nullopt;

    // useful for detect nothing
    using nothing_t = meta::remove_cvref_t<decltype(nothing)>;
#endif // NMTOOLS_META_MAKE_MAYBE_TYPE


#ifndef NMTOOLS_META_MAKE_UNSIGNED
#define NMTOOLS_META_MAKE_UNSIGNED

    /**
     * @brief define make_unsigned to use std::make_unsigned
     * 
     * @tparam T 
     */
    template <typename T>
    struct make_unsigned : ::std::make_unsigned<T> {};

    template <typename T>
    using make_unsigned_t = type_t<make_unsigned<T>>;
#endif // NMTOOLS_META_MAKE_UNSIGNED


#ifndef NMTOOLS_META_MAKE_TUPLE
#define NMTOOLS_META_MAKE_TUPLE

    /**
     * @brief define meta::make_tuple to return std::tuple
     * 
     * @tparam Ts 
     */
    template <typename...Ts>
    struct make_tuple
    {
        using type = ::std::tuple<Ts...>;
    }; // make_tuple

    template <typename...Ts>
    using make_tuple_t = type_t<make_tuple<Ts...>>;
#endif // NMTOOLS_META_MAKE_TUPLE

    // TODO: add make_tuple, make_either...
} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRANSFORM_HPP