#ifndef NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_NDARRAY_MAX_SIZE_HPP
#define NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_NDARRAY_MAX_SIZE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    
    /**
     * @brief Given hybrid ndarray and desired new maximum size, create
     * new hybrid ndarray that has the desired new max size.
     * 
     * @tparam T 
     * @tparam N desired new maximum size
     * @tparam typename 
     * @todo use specific error type as default, instead of void
     */
    template <typename T, auto N, typename=void>
    struct resize_hybrid_ndarray_max_size
    {
        // TODO: use specific type to represent error
        using type = void;
    }; // resize_hybrid_ndarray_max_size

    template <typename T, auto N>
    using resize_hybrid_ndarray_max_size_t = type_t<resize_hybrid_ndarray_max_size<T,N>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_RESIZE_HYBRID_NDARRAY_MAX_SIZE_HPP