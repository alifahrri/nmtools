#ifndef NMTOOLS_META_BITS_TRAITS_IS_FIXED_SHAPE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FIXED_SHAPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_shape.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_fixed_shape
    {
        static constexpr auto value = [](){
            auto fixed_shape = fixed_shape_v<T>;
            return !is_fail_v<decltype(fixed_shape)>;
        }();
    }; // is_fixed_shape

    template <typename T, typename=void>
    constexpr inline auto is_fixed_shape_v = is_fixed_shape<T>::value;

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_FIXED_SHAPE_HPP