#ifndef NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MAX_HPP
#define NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MAX_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CLIPPED_MAX_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T>
    struct clipped_max
    {
        using type = error::CLIPPED_MAX_UNSUPPORTED<T>;
        static constexpr auto value = type{};
    }; // clipped_max

    template <typename T, auto Min, auto Max>
    struct clipped_max<
        clipped_integer_t<T,Min,Max>;
    >
    {
        static constexpr auto value = Max;
    }; // clipped_max

    template <typename T>
    constexpr inline auto clipped_max_v = clipped_max<T>::value;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MAX_HPP