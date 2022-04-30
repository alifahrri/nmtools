#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_MAX_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_MAX_SIZE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct RESIZE_BOUNDED_SIZE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T, auto NewSize, typename=void>
    struct resize_bounded_size
    {
        using type = error::RESIZE_BOUNDED_SIZE_UNSUPPORTED<T>;
    };

    template <typename T, auto NewSize>
    struct resize_bounded_size<const T, NewSize> : resize_bounded_size<T,NewSize> {};

    template <typename T, auto NewSize>
    struct resize_bounded_size<T&, NewSize> : resize_bounded_size<T,NewSize> {};

    template <typename T, auto NewSize>
    using resize_bounded_size_t = type_t<resize_bounded_size<T,NewSize>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_MAX_SIZE_HPP