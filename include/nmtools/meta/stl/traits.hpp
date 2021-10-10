#ifndef NMTOOLS_META_STL_TRAITS_HPP
#define NMTOOLS_META_STL_TRAITS_HPP

#include "nmtools/meta/traits.hpp"

#include <optional>

namespace nmtools::meta
{
    // std::nullopt is nothing type
    template <>
    struct is_nothing<::std::nullopt_t> : std::true_type {};

    template <typename left_t, typename right_t>
    struct is_either<std::variant<left_t,right_t>> : std::true_type {};

    template <typename T>
    struct is_maybe<std::optional<T>> : std::true_type {};

    template <typename ...Args>
    struct is_tuple<std::tuple<Args...>> : std::true_type {};

    /**
     * @brief check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T, auto N>
    struct is_integral_constant<std::integral_constant<T,N>> : true_type {};

#if defined(NMTOOLS_HAS_VECTOR) && (NMTOOLS_HAS_VECTOR)
    template <>
    struct is_bit_reference<std::vector<bool>::reference> : std::true_type {};
#endif

    template <typename T, size_t N>
    struct fixed_index_array_size<std::array<T,N>,std::enable_if_t<is_index_v<T>>>
    {
        static constexpr auto value = N;
    };

    template <typename...Ts>
    struct fixed_index_array_size<std::tuple<Ts...>,std::enable_if_t<(is_index_v<Ts> && ...)>>
    {
        static constexpr auto value = sizeof...(Ts);
    };

    template <typename T, size_t N>
    struct is_fixed_index_array<std::array<T,N>,std::enable_if_t<is_index_v<T>>> : std::true_type {};

    template <typename...Ts>
    struct is_fixed_index_array<std::tuple<Ts...>,std::enable_if_t<(is_index_v<Ts> && ...)>> : std::true_type {};

    template <typename...Ts>
    struct is_constant_index_array<std::tuple<Ts...>,std::enable_if_t<(is_constant_index_v<Ts> && ...)>> : std::true_type {};

    // some edge case for array
    template <typename T, size_t N>
    struct is_constant_index_array<std::array<T,N>,std::enable_if_t<is_constant_index_v<T>>> : std::true_type {};

#if defined(NMTOOLS_HAS_VECTOR) && (NMTOOLS_HAS_VECTOR)
    template <typename T>
    struct is_dynamic_index_array<std::vector<T>,std::enable_if_t<is_index_v<T>>> : std::true_type {};
#endif // NMTOOLS_HAS_VECTOR

    template <typename T>
    struct get_maybe_type<std::optional<T>>
    {
        using type = T;
    };

    template <int value>
    struct is_signed<std::integral_constant<int,value>> : std::true_type {};

    template <size_t value>
    struct is_signed<std::integral_constant<size_t,value>> : std::false_type {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRAITS_HPP