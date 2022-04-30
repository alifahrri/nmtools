#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_MAX_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_MAX_DIM_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct RESIZE_BOUNDED_DIM_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T, auto NewDim, typename=void>
    struct resize_bounded_dim
    {
        using type = error::RESIZE_BOUNDED_DIM_UNSUPPORTED<T>;
    };

    template <typename T, auto NewDim>
    struct resize_bounded_dim<const T, NewDim> : resize_bounded_dim<T,NewDim> {};

    template <typename T, auto NewDim>
    struct resize_bounded_dim<T&, NewDim> : resize_bounded_dim<T,NewDim> {};

    template <typename T, auto NewDim>
    using resize_bounded_dim_t = type_t<resize_bounded_dim<T,NewDim>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_MAX_DIM_HPP