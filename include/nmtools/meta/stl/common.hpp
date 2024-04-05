#ifndef NMTOOLS_META_STL_COMMON_HPP
#define NMTOOLS_META_STL_COMMON_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"

#include <vector>
#include <variant>
#include <array>
#include <tuple>
#include <optional>

namespace nmtools::meta
{
    #ifndef NMTOOLS_META_MAKE_SEQUENCE
    #define NMTOOLS_META_MAKE_SEQUENCE

    template <typename T, typename Allocator>
    struct make_sequence_type
    {
        static constexpr auto vtype = [](){
            if constexpr (is_none_v<Allocator>) {
                using type = std::vector<T>;
                return as_value_v<type>;
            } else {
                using type = std::vector<T,Allocator>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T, typename Allocator=none_t>
    using make_sequence_type_t = type_t<make_sequence_type<T,Allocator>>;

    #ifndef nmtools_list
    #define nmtools_list ::std::vector
    #endif

    #endif // NMTOOLS_META_MAKE_SEQUENCE

    #ifndef NMTOOLS_META_MAKE_EITHER
    #define NMTOOLS_META_MAKE_EITHER

    template <typename Left, typename Right, typename>
    struct make_either_type
    {
        using type = std::variant<Left,Right>;
    };

    template <typename Left, typename Right>
    using make_either_type_t = type_t<make_either_type<Left,Right>>;

    // doesn't support CTAD
    #define nmtools_either ::nmtools::meta::make_either_type_t
    #endif // NMTOOLS_META_MAKE_EITHER

    #if !defined(NMTOOLS_META_MAKE_VECTOR)
    #define NMTOOLS_META_MAKE_VECTOR

    template <typename T, typename>
    struct make_vector
    {
        using type = std::vector<T>;
    }; // make_vector

    template <typename T>
    using make_vector_t = type_t<make_vector<T>>;

    #endif // NMTOOLS_META_MAKE_VECTOR

    #ifndef NMTOOLS_META_MAKE_ARRAY_TYPE
    #define NMTOOLS_META_MAKE_ARRAY_TYPE

    template <typename T, size_t N, typename>
    struct make_array_type
    {
        using type = std::array<T,N>;
    }; // make_array_type

    template <typename T, size_t N>
    using make_array_type_t = type_t<make_array_type<T,N>>;

    // alias template doesn't have ctad, use macro
    #define nmtools_array ::std::array
    #endif // NMTOOLS_META_MAKE_ARRAY_TYPE

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
    using make_tuple_type_t = type_t<make_tuple<Ts...>>;

    // alias template doesn't have ctad:
    // https://godbolt.org/z/51zMTrEGK
    // so use macro for now
    #define nmtools_tuple ::std::tuple
    #endif // NMTOOLS_META_MAKE_TUPLE

    #ifndef NMTOOLS_META_MAKE_MAYBE_TYPE
    #define NMTOOLS_META_MAKE_MAYBE_TYPE
    template <typename T, typename>
    struct make_maybe_type
    {
        using type = std::optional<T>;
    }; // make_maybe_type

    template <typename T>
    using make_maybe_type_t = type_t<make_maybe_type<T>>;

    // TODO: remove
    // std::nullopt_t has no default constructor
    inline constexpr auto nothing = ::std::nullopt;

    // constant to represents nothing type
    inline constexpr auto Nothing = ::std::nullopt;

    // useful for detect nothing
    using nothing_t = meta::remove_cvref_t<decltype(nothing)>;

    // alias template doesn't have ctad:
    // https://godbolt.org/z/51zMTrEGK
    // so use macro for now
    #define nmtools_maybe ::std::optional
    #endif // NMTOOLS_META_MAKE_MAYBE_TYPE
} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_COMMON_HPP