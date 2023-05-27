#ifndef NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_NDARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_NDARRAY_HPP

#include "nmtools/meta/bits/traits/is_fixed_size_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_hybrid_ndarray.hpp"

namespace nmtools::meta
{
    /**
     * @brief Check if type T is dynamic ndarray.
     * 
     * Default implementation check if T is fixed-size of hybrid ndarray,
     * if both return false, then assume T is dynamic.
     *
     * @tparam T type to check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_dynamic_ndarray
    {
        static constexpr auto value = [](){
            // get_element_type defined in transform, while transform
            // depends on this file hence may create circular dependency
            // TODO: also check get_element_type return numeric concept
            // using element_t = get_element_type_t<T>;
            if (is_fixed_size_ndarray_v<T> || is_hybrid_ndarray_v<T>) {
                return false;
            } else {
                return true;
            }
        }();
    }; // is_dynamic_ndarray

    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool is_dynamic_ndarray_v = is_dynamic_ndarray<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_IS_DYNAMIC_NDARRAY_HPP