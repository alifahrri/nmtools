#ifndef NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_SIZE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_SIZE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/array/bounded_size.hpp"
#include "nmtools/meta/bits/traits/is_fail.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_bounded_size
    {
        static constexpr auto value = [](){
            auto bounded_size = bounded_size_v<T>;
            return !is_fail_v<decltype(bounded_size)>;
        }();
    };

    template <typename T>
    constexpr inline auto is_bounded_size_v = is_bounded_size<T>::value;
    
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_BOUNDED_SIZE_HPP