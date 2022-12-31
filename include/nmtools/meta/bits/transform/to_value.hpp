#ifndef NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/promote_index.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TO_VALUE_UNSUPPORTED : detail::fail_t {};
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
    struct to_value
    {
        static inline constexpr auto value = error::TO_VALUE_UNSUPPORTED<T>{};
    }; // to_value

    template <typename T>
    struct to_value <const T> : to_value<T> {};

    template <typename T>
    struct to_value <T&> : to_value<T> {};

    template <typename T, T v>
    struct to_value<integral_constant<T,v>>
    {
        static constexpr auto value = v;
    };

    template <>
    struct to_value<none_t>
    {
        static constexpr auto value = none_t{};
    };

    // nmtools' true_type & false_type is not an alias to integral_constant
    template <> struct to_value<true_type>
    { static constexpr auto value = true; };

    template <> struct to_value<false_type>
    { static constexpr auto value = false; };

    // converting nmtools' clipped_integer using meta::to_value means
    // converting the max value to value array
    // note that currently the min value is ignored.
    // this (using max value) is mostly useful for indexing function (where min=0, max=N)
    // to carry the information about maximum number of elements per axis
    // hence we can deduce the maximum number of elements to deduce the type of buffer at compile time

    template <template<typename...>typename Tuple, typename...T, auto...Min, auto...Max>
    struct to_value<
        Tuple<clipped_integer_t<T,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<T,Min,Max>...>> >
    >
    {
        using index_t = promote_index_t<T...>;
        static constexpr auto value = nmtools_array{index_t(Max)...};
    }; // to_value

    template <template<typename,auto>typename Array, typename T, auto Min, auto Max, auto N>
    struct to_value<
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
    }; // to_value

    template <typename T>
    constexpr inline auto to_value_v = to_value<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP