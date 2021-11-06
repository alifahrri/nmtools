#ifndef NMTOOLS_META_BITS_TRAITS_IS_HYBRID_NDARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_HYBRID_NDARRAY_HPP

#include "nmtools/meta/bits/array/hybrid_ndarray_max_size.hpp"
#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_hybrid_ndarray
    {
        static constexpr auto value = [](){
            using hybrid_max_type = type_t<hybrid_ndarray_max_size<T>>;
            if constexpr (is_same_v<detail::fail_t,hybrid_max_type>) {
                return false;
            } else {
                return true;
            }
        }();
    }; // is_hybrid_ndarray

    template <typename T>
    inline constexpr bool is_hybrid_ndarray_v = is_hybrid_ndarray<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_HYBRID_NDARRAY_HPP