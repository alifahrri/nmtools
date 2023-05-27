#ifndef NMTOOLS_META_BITS_ARRAY_FIXED_NDARRAY_SHAPE
#define NMTOOLS_META_BITS_ARRAY_FIXED_NDARRAY_SHAPE

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/nested_array_size.hpp"
#include "nmtools/meta/bits/array/nested_array_dim.hpp"
#include "nmtools/meta/bits/array/remove_nested_array_dim.hpp"
#include "nmtools/meta/bits/traits/is_bounded_array.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"

#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

#include "nmtools/meta/loop.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FIXED_SHAPE_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief get fixed-array size at compile-time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T type to check
     * @tparam typename optional for sfinae
     */
    template <typename T, typename=void>
    struct fixed_ndarray_shape
    {
        /**
         * @brief get the shape of ndarray.
         *
         * Dispatched code based on the attributes, with the following order:
         * - T is nested array and has fixed-size
         * - T is bounded array
         * - fail
         * 
         * @return constexpr auto 
         */
        static constexpr auto value = [](){
            // check for fixed-size array (that has tuple_size_v)
            if constexpr (nested_array_size_v<T> > 0) {
                // nested_array_dim_v mimics std rank_v
                // nested_array_size_v mimics std extent_v
                constexpr auto dim = nested_array_dim_v<T>;
                using array_t = typename make_array_type<size_t,dim>::type;
                auto shape = array_t{};
                template_for<dim>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    using nested_t = remove_nested_array_dim_t<T,i>;
                    shape[i] = nested_array_size_v<nested_t>;
                });
                return shape;
            }
            // fail otherwise
            else return detail::fail_t{};
        }();
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    };

    /**
     * @brief helper variable template to get fixed-array size at compile-time.
     * well-formed specialization should have `value` and `value_type`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr auto fixed_ndarray_shape_v = fixed_ndarray_shape<T>::value;

    #ifdef __OPENCL_VERSION__
    template <typename T>
    struct fixed_ndarray_shape<T,enable_if_t<has_address_space_v<T>>> : fixed_ndarray_shape<remove_address_space_t<T>> {};
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_ARRAY_FIXED_NDARRAY_SHAPE