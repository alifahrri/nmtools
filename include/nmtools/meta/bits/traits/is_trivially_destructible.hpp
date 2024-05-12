#ifndef NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include "nmtools/meta/builtins.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_pod.hpp"

namespace nmtools::meta
{
    template <typename T, typename=void>
    struct is_trivially_destructible
    {
        static constexpr auto value = [](){
            #ifdef NMTOOLS_IS_TRIVIALLY_DESTRUCTIBLE
            return NMTOOLS_IS_TRIVIALLY_DESTRUCTIBLE(T);
            #elif defined(NMTOOLS_HAS_TRIVIAL_DESTRUCTOR)
            return NMTOOLS_HAS_TRIVIAL_DESTRUCTOR(T);
            #else
            return is_pod_v<T>;
            #endif
        }();
    }; // is_trivially_destructible

    template <typename T>
    constexpr inline auto is_trivially_destructible_v = is_trivially_destructible<T>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP