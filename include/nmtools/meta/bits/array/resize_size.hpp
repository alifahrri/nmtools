#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_SIZE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct RESIZE_SIZE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, auto NewSize, typename=void>
    struct resize_size
    {
        using type = error::RESIZE_SIZE_UNSUPPORTED<T,as_type<NewSize>>;
    };

    template <typename T, auto NewSize>
    struct resize_size<const T,NewSize> : resize_size<T,NewSize> {};

    template <typename T, auto NewSize>
    struct resize_size<T&,NewSize> : resize_size<T,NewSize> {};

    template <typename T, auto NewSize>
    using resize_size_t = type_t<resize_size<T,NewSize>>;

    template <typename T, auto N, auto M>
    struct resize_size<T[N],M>
    {
        using type = nmtools_array<T,M>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_SIZE_HPP