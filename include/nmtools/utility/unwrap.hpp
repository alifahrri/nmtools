#ifndef NMTOOLS_UTILITY_UNWRAP_HPP
#define NMTOOLS_UTILITY_UNWRAP_HPP

#include "nmtools/meta.hpp"

namespace nmtools
{
    template <typename T>
    constexpr auto unwrap(const T& t)
    {
        if constexpr (meta::is_maybe_v<T>) {
            return *t;
        } else {
            return t;
        }
    }
}
#endif // NMTOOLS_UTILITY_UNWRAP_HPP