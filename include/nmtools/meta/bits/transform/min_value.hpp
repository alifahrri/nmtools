#ifndef NMTOOLS_META_BITS_TRANSFORM_MIN_VALUE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_MIN_VALUE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/promote_index.hpp"
#include "nmtools/meta/bits/transform/clipped_max.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct MIN_VALUE_UNSUPPORTED : detail::fail_t {};
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
    struct min_value
    {
        static inline constexpr auto value = error::MIN_VALUE_UNSUPPORTED<T>{};
    }; // min_value

    template <typename T>
    struct min_value <const T> : min_value<T> {};

    template <typename T>
    struct min_value <T&> : min_value<T> {};

    template <typename T, auto v>
    struct min_value<integral_constant<T,v>>
    {
        static constexpr auto value = v;
    };

    // nmtools' true_type & false_type is not an alias to integral_constant
    template <> struct min_value<true_type>
    { static constexpr auto value = true; };

    template <> struct min_value<false_type>
    { static constexpr auto value = false; };

    // converting nmtools' clipped_integer using meta::min_value means
    // converting the max value to value array
    // note that currently the min value is ignored.
    // this (using max value) is mostly useful for indexing function (where min=0, max=N)
    // to carry the information about maximum number of elements per axis
    // hence we can deduce the maximum number of elements to deduce the type of buffer at compile time

    template <typename T, auto Min, auto Max>
    struct min_value<clipped_integer_t<T,Min,Max>>
        : clipped_max<clipped_integer_t<T,Min,Max>>
    {};

    template <typename T>
    constexpr inline auto min_value_v = min_value<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_MIN_VALUE_HPP