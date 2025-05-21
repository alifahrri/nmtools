#ifndef NMTOOLS_META_BITS_TRANSFORM_LEN_HPP
#define NMTOOLS_META_BITS_TRANSFORM_LEN_HPP

#include "nmtools/meta/bits/array/fixed_ndarray_shape.hpp"
#include "nmtools/meta/bits/traits/has_tuple_size.hpp"
#include "nmtools/meta/bits/traits/has_square_bracket.hpp"
#include "nmtools/meta/bits/traits/has_bracket.hpp"
#include "nmtools/meta/bits/traits/has_template_get.hpp"
#include "nmtools/meta/bits/traits/is_fixed_size_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_const.hpp"
#include "nmtools/meta/bits/traits/is_reference.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    // TODO: minimize dependencies to other metafunctions,
    // this metafunctions should be simple.
    // reverse the dependency between len and fixed_ndarray_shape
    /**
     * @brief Helper metafunction for convinient tuple-size
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct len
    {
        static constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<T>) {
                // similar to python, when len is used on ndarray
                // return the size of first axis
                constexpr auto shape = fixed_ndarray_shape_v<T>;
                using shape_t = remove_cvref_t<decltype(shape)>;
                if constexpr (has_square_bracket_v<shape_t,size_t>) {
                    return shape[0];
                } else if constexpr (has_bracket_v<shape_t,size_t>) {
                    return shape(0);
                } else if constexpr (has_template_get_v<shape_t>) {
                    return get<0>(shape);
                }
            } else {
                return -1;
            }
        }();
    };

    template <typename T>
    constexpr inline auto len_v = len<T>::value;

    template <typename T>
    struct len<const T> : len<T> {};

    template <typename T>
    struct len<T&> : len<T> {};

    template <typename T, size_t N>
    struct len<T[N], enable_if_t<!(is_const_v<T> || is_lvalue_reference_v<T> || is_rvalue_reference_v<T>)>>
    {
        static constexpr auto value = N;
    };

    #ifdef __OPENCL_VERSION__
    #if 0
    // NOTE: the following is ambiguous
    template <typename T>
    struct len<T,enable_if_t<has_address_space_v<T>>> : len<remove_address_space_t<T>> {};
    #else
    template <typename T>
    struct len<const global T> : len<T> {};

    template <typename T>
    struct len<const local T> : len<T> {};

    template <typename T>
    struct len<const constant T> : len<T> {};

    template <typename T>
    struct len<const private T> : len<T> {};
    #endif
    #endif // __OPENCL_VERSION__
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_LEN_HPP