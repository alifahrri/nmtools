#ifndef NMTOOLS_META_STL_TRAITS_HPP
#define NMTOOLS_META_STL_TRAITS_HPP

#include "nmtools/meta/traits.hpp"

#include <type_traits>
#include <variant>
#include <tuple>
#include <optional>
// TODO: remove, no need to check for include
#if __has_include(<vector>)
    #include <vector>
    #define NMTOOLS_HAS_STL_VECTOR 1
#else
    #define NMTOOLS_HAS_STL_VECTOR 0
#endif

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

    template <typename T>
    struct get_maybe_type<std::optional<T>>
    {
        using type = T;
    };

    template <int value>
    struct is_signed<std::integral_constant<int,value>> : std::true_type {};

    template <size_t value>
    struct is_signed<std::integral_constant<size_t,value>> : std::false_type {};

    /**
     * @brief specialization of has_tuple_size when tuple_size<T> is well-formed
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_tuple_size<T, void_t<typename std::tuple_size<T>::type>> : true_type {};

    // this allow bool to be considered as "index"
    // TODO: remove
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_index<T, enable_if_t<
        std::is_integral_v<T> || is_integral_constant_v<T>
    > > : true_type {};

// TODO: no need to use ifdef, can safely assume already have vector
#if defined(NMTOOLS_HAS_STL_VECTOR) && (NMTOOLS_HAS_STL_VECTOR)
    template <>
    struct is_bit_reference<std::vector<bool>::reference> : std::true_type {};

    template <typename T>
    struct is_ndarray<std::vector<T>>
    {
        // temporarily allow nested vector
        // TODO: drop nested vector support
        static constexpr auto value = is_num_v<T> || is_ndarray_v<T>;
    };

    template <typename T>
    struct is_dynamic_index_array<std::vector<T>,std::enable_if_t<is_index_v<T>>> : std::true_type {};

    template <typename T, typename Allocator>
    struct is_list<std::vector<T,Allocator>> : true_type {};
#endif // NMTOOLS_HAS_VECTOR
} // namespace nmtools::meta

#endif // NMTOOLS_META_STL_TRAITS_HPP