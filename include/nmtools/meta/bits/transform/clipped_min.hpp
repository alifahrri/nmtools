#ifndef NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MIN_HPP
#define NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MIN_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/promote_index.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CLIPPED_MIN_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, typename=void>
    struct clipped_min
    {
        using type = error::CLIPPED_MIN_UNSUPPORTED<T>;
        static constexpr auto value = type{};
    }; // clipped_min

    template <typename T, auto Min, auto Max>
    struct clipped_min<
        clipped_integer_t<T,Min,Max>
    >
    {
        static constexpr auto value = Min;
    }; // clipped_min

    template <typename T>
    constexpr inline auto clipped_min_v = clipped_min<T>::value;

    template <template<typename...>typename Tuple, typename...Ts, auto...Min, auto...Max>
    struct clipped_min<
        Tuple<clipped_integer_t<Ts,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<Ts,Min,Max>...>> >
    >
    {
        using index_t = promote_index_t<Ts...>;
        static constexpr auto value = nmtools_array{index_t(Min)...};
    };
}

#endif // NMTOOLS_META_BITS_TRANSFORM_CLIPPED_MIN_HPP