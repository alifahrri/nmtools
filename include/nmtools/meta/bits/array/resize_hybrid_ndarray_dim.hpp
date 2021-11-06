#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_NDARRAY_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_NDARRAY_DIM_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        /**
         * @brief Default error type for resize_hybrid_ndarray_dim
         * 
         */
        struct RESIZE_HYBRID_ERROR : detail::fail_t {};
    }

    /**
     * @brief Given hybrid ndarray and desired new dim, create
     * new hybrid ndarray that has the desired new dim.
     * 
     * @tparam T 
     * @tparam DIM desired new dimension
     * @tparam typename 
     */
    template <typename T, auto DIM, typename=void>
    struct resize_hybrid_ndarray_dim
    {
        using type = error::RESIZE_HYBRID_ERROR;
    };

    template <typename T, auto N>
    using resize_hybrid_ndarray_dim_t = type_t<resize_hybrid_ndarray_dim<T,N>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_NDARRAY_DIM_HPP