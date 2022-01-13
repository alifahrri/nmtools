#ifndef NMTOOLS_ARRAY_NDARRAY_HPP
#define NMTOOLS_ARRAY_NDARRAY_HPP

#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#ifndef NMTOOLS_DISABLE_DYNAMIC_ARRAY
#include "nmtools/array/ndarray/dynamic.hpp"
#endif // NMTOOLS_DISABLE_DYNAMIC_ARRAY

namespace nmtools::meta
{

#ifndef NMTOOLS_MAKE_DYNAMIC_NDARRAY
#define NMTOOLS_MAKE_DYNAMIC_NDARRAY

    namespace error
    {
        struct DYNAMIC_ARRAY_DISABLED : detail::fail_t {};
    }
    /**
     * @brief Default definition of make_dynamic_ndarray,
     * returns nmtools::array::dynamic_ndarray.
     * 
     * @tparam element_t desired element type of resulting array
     * @todo consider to make this metafunction override-able via global macro
     */
    template <typename element_t>
    struct make_dynamic_ndarray
    {
        using type = error::DYNAMIC_ARRAY_DISABLED;
    }; // make_dynamic_ndarray

    template <typename element_t>
    using make_dynamic_ndarray_t = type_t<make_dynamic_ndarray<element_t>>;

#endif // NMTOOLS_MAKE_DYNAMIC_NDARRAY

} // nmtools::meta

#endif // NMTOOLS_ARRAY_NDARRAY_HPP