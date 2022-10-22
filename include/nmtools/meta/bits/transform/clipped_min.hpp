#ifndef NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MIN_HPP
#define NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MIN_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CLIPPED_MIN_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T>
    struct clipped_min
    {
        using type = error::CLIPPED_MIN_UNSUPPORTED<T>;
        static constexpr auto value = type{};
    }; // clipped_min

    template <typename T, auto Min, auto Max>
    struct clipped_min<
        clipped_integer_t<T,Min,Max>;
    >
    {
        static constexpr auto value = Min;
    }; // clipped_min

    template <typename T>
    constexpr inline auto clipped_min_v = clipped_min<T>::value;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MIN_HPP