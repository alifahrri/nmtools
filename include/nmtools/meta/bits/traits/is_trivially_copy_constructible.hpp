#ifndef NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/add_reference.hpp"
#include "nmtools/meta/bits/traits/is_trivially_constructible.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_trivially_copy_constructible
        : is_trivially_constructible<T,add_lvalue_reference_t<T>>
    {};

    template <typename T>
    constexpr inline auto is_trivially_copy_constructible_v = is_trivially_copy_constructible<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_HPP