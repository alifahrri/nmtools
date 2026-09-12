#ifndef NMTOOLS_BITS_TRAITS_IS_POINTER_HPP
#define NMTOOLS_BITS_TRAITS_IS_POINTER_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_shared_ptr.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_pointer : is_shared_ptr<T> {};

    template <typename T>
    struct is_pointer<T*> : true_type {};

    template <typename T>
    constexpr inline auto is_pointer_v = is_pointer<T>::value;
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_pointer_v;
}

#endif // NMTOOLS_BITS_TRAITS_IS_POINTER_HPP