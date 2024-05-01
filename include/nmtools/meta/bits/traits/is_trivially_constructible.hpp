#ifndef NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#include "nmtools/meta/builtins.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_pod.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_trivially_constructible
    {
        static constexpr auto value = [](){
            #if defined(NMTOOLS_HAS_TRIVIAL_CONSTRUCTOR)
            return NMTOOLS_HAS_TRIVIAL_CONSTRUCTOR(T);
            #else
            return is_pod_v<T>;
            #endif
        }();
    };

    template <typename T>
    constexpr inline auto is_trivially_constructible_v = is_trivially_constructible<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP