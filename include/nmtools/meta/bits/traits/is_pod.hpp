#ifndef NMTOOLS_META_BITS_TRAITS_IS_POD_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_POD_HPP

#include "nmtools/meta/builtins.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_void.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_pod
    {
        static constexpr auto value = [](){
            #ifdef NMTOOLS_IS_POD
            return NMTOOLS_IS_POD(T);
            #else
            return is_num_v<T> || is_void_v<T>;
            #endif // NMTOOLS_IS_POD
        }();
    }; // is_pod

    template <typename T>
    constexpr inline auto is_pod_v = is_pod<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_IS_POD_HPP