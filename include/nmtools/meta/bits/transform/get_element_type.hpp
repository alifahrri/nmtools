#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_ELEMENT_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_ELEMENT_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/nested_array_dim.hpp"
#include "nmtools/meta/bits/array/remove_all_nested_array_dim.hpp"
#include "nmtools/meta/bits/transform/bit_reference_to_bool.hpp"
#include "nmtools/meta/bits/traits/is_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"
#include "nmtools/meta/bits/traits/has_value_type.hpp"

namespace nmtools::meta
{
    // TODO: remove
    /**
     * @brief metafunction to get the value/element type of an ndarray
     * 
     * @tparam T type to test
     * @todo consider use expr to deduce type (e.g. expr::atnd)
     */
    template <typename T>
    struct get_ndarray_value_type
    {
        using type = void;
    };

    /**
     * @brief helper alias template for get_ndarray_value_type
     * 
     * @tparam T type to test
     */
    template <typename T>
    using get_ndarray_value_type_t = typename get_ndarray_value_type<T>::type;

    namespace error
    {
        template <typename...>
        struct GET_ELEMENT_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_element_type
    {
        /**
         * @brief helper function to deduce resulting type
         * 
         * @return constexpr auto 
         * @todo consider use expr to deduce type (e.g. expr::atnd)
         */
        static inline constexpr auto vtype = []()
        {
            if constexpr (nested_array_dim_v<T> > 0) {
                using element_t = remove_all_nested_array_dim_t<T>;
                // TODO: maybe specialize on bool instead of using bit ref to bool
                // note that remove_all_nested_array_dim_t using expression to deduce the type
                // causing vector<bool> deduced to std _Bit_reference instead of bool
                using type = bit_reference_to_bool_t<element_t>;
                return as_value_v<type>;
            }
            // ndarray is more generic
            else if constexpr (is_ndarray_v<T>) {
                using type = get_ndarray_value_type_t<T>;
                return as_value_v<type>;
            }
            else if constexpr (is_integral_constant_v<T>) {
                return as_value_v<typename T::value_type>;
            }
            else if constexpr (has_value_type_v<T>) {
                using type = typename T::value_type;
                if constexpr (is_num_v<type>)
                    return as_value_v<type>;
                else
                    return as_value_v<typename get_element_type<type>::type>;
            }
            else if constexpr (is_num_v<T>)
                return as_value_v<T>;
            else return as_value_v<error::GET_ELEMENT_TYPE_UNSUPPORTED<T>>;
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_element_type

    /**
     * @brief helper alias template for get_element_type
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using get_element_type_t = typename get_element_type<T>::type;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_ELEMENT_TYPE_HPP