#ifndef NMTOOLS_UTILITY_HAS_VALUE_HPP
#define NMTOOLS_UTILITY_HAS_VALUE_HPP

#include "nmtools/meta.hpp"

namespace nmtools
{
    template <typename T>
    constexpr auto has_value(const T& t) -> bool
    {
        if constexpr (meta::is_maybe_v<T>) {
            return static_cast<bool>(t);
        } else {
            return true;
        }
    }
}

#endif // NMTOOLS_UTILITY_HAS_VALUE_HPP