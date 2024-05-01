#ifndef NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#include "nmtools/meta/builtins.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_pod.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_trivially_copyable
    {
        static constexpr auto value = [](){
            #if defined(NMTOOLS_HAS_TRIVIAL_COPY)
            return NMTOOLS_HAS_TRIVIAL_COPY(T);
            #else
            return is_pod_v<T>;
            #endif
        }();
    };

    template <typename T>
    constexpr inline auto is_trivially_copyable_v = is_trivially_copyable<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_COPYABLE_HPP