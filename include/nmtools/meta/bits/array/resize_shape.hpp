#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_SHAPE_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_SHAPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct RESIZE_SHAPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T, typename NewShape, typename=void>
    struct resize_shape
    {
        using type = error::RESIZE_SHAPE_UNSUPPORTED<T,NewShape>;
    };

    template <typename T, typename NewShape>
    struct resize_shape<const T, NewShape> : resize_shape<T,NewShape> {};

    template <typename T, typename NewShape>
    struct resize_shape<T&, NewShape> : resize_shape<T,NewShape> {};

    template <typename T,typename NewSize>
    using resize_shape_t = type_t<resize_shape<T,NewSize>>;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_SHAPE_HPP