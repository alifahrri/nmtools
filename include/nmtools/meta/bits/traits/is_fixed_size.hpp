#ifndef NMTOOLS_META_BITS_TRAITS_IS_FIXED_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_FIXED_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/fixed_size.hpp"
#include "nmtools/meta/bits/traits/is_fail.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_fixed_size
    {
        static constexpr auto value = [](){
            auto size = fixed_size_v<T>;
            using size_type = decltype(size);
            return !is_fail_v<size_type>;
        }();
    }; // is_fixed_size

    template <typename T>
    struct is_fixed_size<const T> : is_fixed_size<T> {};

    template <typename T>
    struct is_fixed_size<T&> : is_fixed_size<T> {};

    template <typename T>
    constexpr inline auto is_fixed_size_v = is_fixed_size<T>::value;

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_FIXED_SIZE_HPP