#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_DIM_HPP
#define NMTOOLS_META_BITS_ARRAY_FIXED_DIM_HPP

#include "nmtools/meta/bits/traits/is_fixed_size_ndarray.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/array/nested_array_dim.hpp"
#include "nmtools/meta/bits/array/fixed_ndarray_shape.hpp"
#include "nmtools/meta/bits/traits/is_void.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct FIXED_DIM_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    // TODO: remove, put the logic on fixed_dim instead
    /**
     * @brief get fixed-array dimension
     *
     * Default implementation will check if type T is fixed-size ndarray
     * and get the number of dimension from the shape then set value and value_type
     * accordingly, otherwise value_type is void and value is fail_t{}.
     * 
     * @tparam T type to check
     * @tparam typename customization point
     * @see is_fixed_size_ndarray
     * @see fixed_ndarray_shape
     * @note not to be confused with fixed_dim, in which *may* return the number of dimension for runtime array
     */
    template <typename T, typename=void>
    struct fixed_ndarray_dim
    {
        static constexpr auto _get()
        {
            if constexpr (is_fixed_size_ndarray_v<T>) {
                auto shape = fixed_ndarray_shape_v<T>;
                auto dim   = len_v<decltype(shape)>;
                return dim;
            }
            else return detail::fail_t{};
        } // _get()
        static constexpr auto value = _get();
        // TODO: use specific error type
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_dim

    /**
     * @brief helper variable template for fixed_ndarray_dim
     * 
     * @tparam T 
     */
    template <typename T>
    inline static constexpr auto fixed_ndarray_dim_v = fixed_ndarray_dim<T>::value;

    // TODO: maybe rename to dim instead
    // TODO: cleanup
    /**
     * @brief check if type T has fixed-dimension
     * 
     * @tparam T type to check
     * @tparam typename 
     * @see fixed_ndarray_dim
     * @see nested_array_dim_v
     * @note not to be confused with fixed_ndarray_dim, in which *only* return the number of dimension for fixed-size array
     */
    template <typename T, typename=void>
    struct fixed_dim
    {
        static constexpr auto value = [](){
            // for fixed-size ndarray, read dimension from fixed_ndarray_dim,
            // which simply count the number of shape
            using dim_t = fixed_ndarray_dim<T>;
            using value_type = typename dim_t::value_type;
            if constexpr (!is_void_v<value_type>)
                return dim_t::value;
            // TODO: try to compute from fixed_shape
            // for nested array, while the shape may only known at runtime,
            // the dimension can be known at compile time
            else if constexpr (nested_array_dim_v<T> > 0)
                return nested_array_dim_v<T>;
            else return detail::Fail;
        }();
        // TODO: use specific error type
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // fixed_dim

    /**
     * @brief helper variable template for fixed_dim
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline static constexpr auto fixed_dim_v = fixed_dim<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_FIXED_DIM_HPP