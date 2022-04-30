#ifndef NMTOOLS_META_BITS_TRAITS_IS_FIXED_DIM_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FIXED_DIM_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_dim.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_reference.hpp"
#include "nmtools/meta/bits/traits/is_const.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_fixed_dim
    {
        static constexpr auto value = [](){
            auto fixed_dim = fixed_dim_v<T>;
            return is_num_v<decltype(fixed_dim)>;
        }();
    };

    template <typename T>
    struct is_fixed_dim<const T> : is_fixed_dim<T> {};

    template <typename T>
    constexpr inline auto is_fixed_dim_v = is_fixed_dim<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_FIXED_DIM_HPP