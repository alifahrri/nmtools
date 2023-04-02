#ifndef NMTOOLS_META_BITS_IS_FIXED_SIZE_NDARRAY
#define NMTOOLS_META_BITS_IS_FIXED_SIZE_NDARRAY

#include "nmtools/meta/common.hpp"

#include "nmtools/meta/bits/array/fixed_ndarray_shape.hpp"
#include "nmtools/meta/bits/traits/is_void.hpp"
#include "nmtools/meta/bits/traits/is_fail.hpp"

namespace nmtools::meta
{
    /**
     * @brief check if given type T is fixed-size array
     *
     * Default implementation check if calls to fixed_ndarray_shape returns successful (value_type not void),
     * returns true for such case, false otherwise.
     * 
     * @tparam T type to check
     * @tparam typename customization point
     * @see fixed_ndarray_shape
     */
    template <typename T, typename=void>
    struct is_fixed_size_ndarray
    {
        static constexpr auto value = [](){
            using fixed_size_t = fixed_ndarray_shape<T>;
            #if 0
            using value_type   = typename fixed_size_t::value_type;
            #else
            using value_type = decltype(fixed_size_t::value);
            #endif
            // TODO: use fail type instead of void
            if constexpr (!is_void_v<value_type> && !is_fail_v<value_type>)
                return true;
            else return false;
        }();
    }; // is_fixed_size_ndarray

    /**
     * @brief helper variable template to check if given type T is n-dimensional array that shape is known at compile-time
     * 
     * @tparam T type to check
     */
    template <typename T>
    nmtools_meta_variable_attribute
    inline constexpr bool is_fixed_size_ndarray_v = is_fixed_size_ndarray<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_IS_FIXED_SIZE_NDARRAY