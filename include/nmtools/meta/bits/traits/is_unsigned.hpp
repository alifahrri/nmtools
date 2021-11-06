#ifndef NMTOOLS_META_BITS_TRAITS_IS_UNSIGNED_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_UNSIGNED_HPP

#include "nmtools/meta/bits/traits/is_signed.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_unsigned
    {
        static constexpr auto value = !is_signed_v<T>;
    }; // is_unsigned

    template <typename T>
    inline constexpr auto is_unsigned_v = is_unsigned<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_UNSIGNED_HPP