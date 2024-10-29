#ifndef NMTOOLS_META_BITS_TRANSFORM_MAX_VALUE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_MAX_VALUE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/promote_index.hpp"
#include "nmtools/meta/bits/transform/clipped_max.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct MAX_VALUE_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Convert constant index to value
     * 
     * If T is tuple, it is expected to transform to array
     * for easy handling as value.
     * 
     * @tparam T 
     */
    template <typename T,typename=void>
    struct max_value
    {
        static inline constexpr auto value = error::MAX_VALUE_UNSUPPORTED<T>{};
    }; // max_value

    template <typename T>
    struct max_value <const T> : max_value<T> {};

    template <typename T>
    struct max_value <T&> : max_value<T> {};

    template <typename T, auto v>
    struct max_value<integral_constant<T,v>>
    {
        static constexpr auto value = v;
    };

    // nmtools' true_type & false_type is not an alias to integral_constant
    template <> struct max_value<true_type>
    { static constexpr auto value = true; };

    template <> struct max_value<false_type>
    { static constexpr auto value = false; };

    // converting nmtools' clipped_integer using meta::max_value means
    // converting the max value to value array
    // note that currently the min value is ignored.
    // this (using max value) is mostly useful for indexing function (where min=0, max=N)
    // to carry the information about maximum number of elements per axis
    // hence we can deduce the maximum number of elements to deduce the type of buffer at compile time

    template <template<typename...>typename Tuple, typename...T, auto...Min, auto...Max>
    struct max_value<
        Tuple<clipped_integer_t<T,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<T,Min,Max>...>> && sizeof...(T)>
    >
    {
        using index_t = promote_index_t<T...>;
        static constexpr auto value = nmtools_array{index_t(Max)...};
    }; // max_value

    template <template<typename...>typename tuple, typename...Ts>
    struct max_value<
        tuple<Ts...>
        , enable_if_t< is_tuple_v<tuple<Ts...>> && (is_constant_index_v<Ts> && ...) && sizeof...(Ts)>
    > {
        using index_t = promote_index_t<decltype(Ts::value)...>;
        static constexpr auto value = nmtools_array{index_t(Ts::value)...};
    }; // max_value

    template <template<typename,auto>typename Array, typename T, auto Min, auto Max, auto N>
    struct max_value<
        Array<clipped_integer_t<T,Min,Max>,N>
    >
    {
        static constexpr auto value = [](){
            using type = nmtools_array<T,N>;
            auto result = type{};
            for (size_t i=0; i<N; i++) {
                result[i] = Max;
            }
            return result;
        }();
    }; // max_value

    template <typename T, auto Min, auto Max>
    struct max_value<clipped_integer_t<T,Min,Max>>
        : clipped_max<clipped_integer_t<T,Min,Max>>
    {};

    template <typename T>
    constexpr inline auto max_value_v = max_value<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_MAX_VALUE_HPP