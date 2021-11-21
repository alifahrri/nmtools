#ifndef NMTOOLS_UTILITY_FORWARD_HPP
#define NMTOOLS_UTILITY_FORWARD_HPP

#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/meta/bits/traits/is_reference.hpp"

namespace nmtools
{
    template <typename T>
    inline constexpr T&& forward(meta::remove_reference_t<T>& t) noexcept
    {
        return static_cast<T&&>(t);
    }

    template <typename T>
    inline constexpr T&& forward(meta::remove_reference_t<T>&& t) noexcept
    {
        static_assert( !meta::is_lvalue_reference_v<T> );
        return static_cast<T&&>(t);
    }
} // namespace nmtools

#endif // NMTOOLS_UTILITY_FORWARD_HPP