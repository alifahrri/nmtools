#ifndef NMTOOLS_META_BITS_TRAITS_IS_FIXED_DIM_NDARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FIXED_DIM_NDARRAY_HPP

#include "nmtools/meta/bits/array/fixed_dim.hpp"
#include "nmtools/meta/bits/traits/is_void.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if type T is fixed-dimension ndarray
     *
     * Default implementation checks if fixed_ndarray_dim<T>
     * has value_type that is not void.
     * 
     * @tparam T type to check
     * @tparam typename customization point
     * @see fixed_dim
     */
    template <typename T, typename=void>
    struct is_fixed_dim_ndarray
    {
        static constexpr auto value = [](){
            // for fixed-size ndarray, read dimension from fixed_dim,
            // which simply count the number of shape
            constexpr auto value = fixed_dim_v<T>;
            using value_type = remove_cvref_t<decltype(value)>;
            return !(is_void_v<value_type> || is_fail_v<value_type>);
        }();
    }; // is_fixed_dim_ndarray

    /**
     * @brief helper variable template for is_fixed_dim_ndarray
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto is_fixed_dim_ndarray_v = is_fixed_dim_ndarray<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_FIXED_DIM_NDARRAY_HPP