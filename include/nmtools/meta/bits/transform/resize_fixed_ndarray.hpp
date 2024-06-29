#ifndef NMTOOLS_META_BITS_TRANSFORM_RESIZE_FIXED_NDARRAY_HPP
#define NMTOOLS_META_BITS_TRANSFORM_RESIZE_FIXED_NDARRAY_HPP

// expose nmtools_tuple
#include "nmtools/stl.hpp"
#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct RESIZE_FIXED_NDARRAY_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief resize fixed array
     * 
     * @tparam T original array
     * @tparam U fixed ndarray type containing new shape
     * @tparam typename 
     */
    template <typename T, typename U, typename=void>
    struct resize_fixed_ndarray
    {
        // TODO: use error type
        using type = T;
    }; // resize_fixed_ndarray

    /**
     * @brief helper alias template for resize fixed array
     * 
     * @tparam T original array
     * @tparam U type containing new shape
     */
    template <typename T, typename U>
    using resize_fixed_ndarray_t = type_t<resize_fixed_ndarray<T,U>>;

    template <typename T, typename U, size_t N>
    struct resize_fixed_ndarray<T[N],U,
        enable_if_t<is_fixed_size_ndarray_v<U>>
    >
    {
        using shape_t = nmtools_tuple<ct<N>>;
        using default_ndarray_t = type_t<make_fixed_ndarray<T,shape_t>>;
        using type = resize_fixed_ndarray_t<default_ndarray_t,U>;
    }; // resize_fixed_ndarray
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_RESIZE_FIXED_NDARRAY_HPP