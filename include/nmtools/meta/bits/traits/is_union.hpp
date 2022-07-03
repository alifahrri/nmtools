#ifndef NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP

#include "nmtools/meta/builtins.hpp"
#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_union
    {
        static constexpr auto value = [](){
            #ifdef NMTOOLS_IS_UNION
            return NMTOOLS_IS_UNION(T);
            #else
            // assume union is rarely used
            return false;
            #endif
        }();
    };

    template <typename T>
    constexpr inline auto is_union_v = is_union<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP