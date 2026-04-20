#ifndef NMTOOLS_META_BITS_TRAITS_IS_SHARED_PTR_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_SHARED_PTR_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_shared_ptr : false_type {};

    template <typename T>
    struct is_shared_ptr<const T> : is_shared_ptr<T> {};

    template <typename T>
    struct is_shared_ptr<T&> : is_shared_ptr<T> {};

    template <typename T>
    constexpr inline auto is_shared_ptr_v = is_shared_ptr<T>::value;
} // namespace nmtools::meta

namespace nmtools
{
    using meta::is_shared_ptr_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_SHARED_PTR_HPP