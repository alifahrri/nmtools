#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_DIM_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct RESIZE_DIM_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename T, auto NewDim, typename=void>
    struct resize_dim
    {
        using type = error::RESIZE_DIM_UNSUPPORTED<T>;
    };

    template <typename T, auto NewDim>
    struct resize_dim<const T,NewDim> : resize_dim<T,NewDim> {};

    template <typename T, auto NewDim>
    struct resize_dim<T&,NewDim> : resize_dim<T,NewDim> {};

    template <typename T, auto NewDim>
    using resize_dim_t = type_t<resize_dim<T,NewDim>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_DIM_HPP