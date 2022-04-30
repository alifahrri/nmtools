#ifndef NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_DIM_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_DIM_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/bounded_dim.hpp"
#include "nmtools/meta/bits/traits/is_fail.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_bounded_dim
    {
        static constexpr auto value = [](){
            auto bounded_dim = bounded_dim_v<T>;
            return !is_fail_v<decltype(bounded_dim)>;
        }();
    }; // is_bounded_dim

    template <typename T>
    struct is_bounded_dim<const T> : is_bounded_dim<T> {};

    template <typename T>
    struct is_bounded_dim<T&> : is_bounded_dim<T> {};

    template <typename T>
    constexpr inline auto is_bounded_dim_v = is_bounded_dim<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_DIM_HPP