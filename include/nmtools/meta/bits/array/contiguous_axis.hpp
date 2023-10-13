#ifndef NMTOOLS_META_BITS_ARRAY_CONTIGUOUS_AXIS_HPP
#define NMTOOLS_META_BITS_ARRAY_CONTIGUOUS_AXIS_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CONTIGUOUS_AXIS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, typename=void>
    struct contiguous_axis
    {
        static constexpr auto value = error::CONTIGUOUS_AXIS_UNSUPPORTED<T>{};
    };

    template <typename T>
    struct contiguous_axis<const T> : contiguous_axis<T> {};

    template <typename T>
    struct contiguous_axis<T&> : contiguous_axis<T> {};

    template <typename T>
    constexpr inline auto contiguous_axis_v = contiguous_axis<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_CONTIGUOUS_AXIS_HPP