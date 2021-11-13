#ifndef NMTOOLS_META_BITS_TRANSFORM_LEN_HPP
#define NMTOOLS_META_BITS_TRANSFORM_LEN_HPP

#include "nmtools/meta/bits/traits/has_tuple_size.hpp"
#include "nmtools/meta/bits/traits/is_fixed_size_ndarray.hpp"
#include "nmtools/meta/bits/array/fixed_ndarray_shape.hpp"
#include "nmtools/meta/bits/traits/has_square_bracket.hpp"
#include "nmtools/meta/bits/traits/has_bracket.hpp"
#include "nmtools/meta/bits/traits/has_template_get.hpp"

// TODO: remove, minimize dependencies to stl
#include <type_traits>
#include <utility>

namespace nmtools::meta
{
    /**
     * @brief Helper metafunction for convinient tuple-size
     * 
     * @tparam T 
     */
    template <typename T>
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
            }
            // TODO: do not return 0, return error type instead?
            else return 0;
        }();
    };

    template <typename T>
    constexpr inline auto len_v = len<T>::value;

    template <typename T>
    struct len<const T&> : len<T> {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_LEN_HPP