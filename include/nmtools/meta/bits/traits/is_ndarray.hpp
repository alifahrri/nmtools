#ifndef NMTOOLS_META_BITS_TRAITS_IS_NDARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NDARRAY_HPP

#include "nmtools/meta/bits/traits/has_at.hpp"
#include "nmtools/meta/bits/traits/has_bracket.hpp"
#include "nmtools/meta/bits/traits/has_square_bracket.hpp"
#include "nmtools/meta/bits/traits/is_fixed_size_ndarray.hpp"
#include "nmtools/meta/bits/array/nested_array_dim.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    // TODO: remove
    /**
     * @brief check if T t{} are:
     * - t[0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename=void>
    struct is_array1d
    {
        // TODO: remove, prefer explicit specialization
        static constexpr inline auto value = [](){
            if constexpr (has_atnd_v<T,size_t>)
                return true;
            // else if constexpr (has_funcnd_v<T,size_t>)
            //     return true;
            else if constexpr (has_square_bracket_v<T,size_t>)
                return true;
            else if constexpr (nested_array_dim_v<T> == 1)
                return true;
            else return false;
        }();
    }; // is_array1d

    /**
     * @brief helper variable template to check if T is 1d array-like
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_array1d_v = is_array1d<T>::value;
} // namespace nmtools::meta

namespace nmtools::meta
{
    /**
     * @addtogroup traits
     * @{
     */

    /**
     * @brief check if given type T is n-dimensional array
     * 
     * Default implementation check for distjunction of fixed-size ndarray, array1d and array2d.
     *
     * @tparam T type to check
     * @tparam typename customization point
     * @see is_fixed_size_ndarray
     */
    template <typename T, typename=void>
    struct is_ndarray
    {
        static constexpr auto value = [](){

            if constexpr (is_fixed_size_ndarray_v<T>)
                return true;
            else return false;
        }();
    }; // is_ndarray

    /**
     * @brief helper variable template to check if T is n-dimensional array
     * 
     * @tparam T type to check
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool is_ndarray_v = is_ndarray<T>::value;

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct is_ndarray<T,enable_if_t<has_address_space_v<T>>> : is_ndarray<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__


    /** @} */ // end group traits

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_NDARRAY_HPP