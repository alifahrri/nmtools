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

#ifndef NMTOOLS_META_MAKE_SIGNED
#define NMTOOLS_META_MAKE_SIGNED

    /**
     * @brief define make_signed to use std::make_signed
     * 
     * @tparam T type to be transformed
     */
    template<typename T>
    struct make_signed : ::std::make_signed<T> {};

    template <typename T>
    using make_signed_t = type_t<make_signed<T>>;
#endif // NMTOOLS_META_MAKE_SIGNED


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

    /**
     * @brief Specialization fo to_value for std types (tuple of int constant)
     * 
     * @tparam Is 
     */
    template <auto...Is>
    struct to_value<
        std::tuple<std::integral_constant<decltype(Is),Is>...>
    >
    {
        using value_type = std::common_type_t<decltype(Is)...>;
        static inline constexpr auto value = std::array<value_type,sizeof...(Is)>{Is...};
    }; // to_value

    template <auto I>
    struct to_value<std::integral_constant<decltype(I),I>>
    {
        static inline constexpr auto value = I;
    }; // to_value
} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRANSFORM_HPP