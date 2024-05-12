#ifndef NMTOOLS_META_BITS_TRAITS_IS_COPY_ASSIGNABLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_COPY_ASSIGNABLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_assignable.hpp"
#include "nmtools/meta/bits/transform/add_const.hpp"
#include "nmtools/meta/bits/transform/add_reference.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_copy_assignable
        : is_assignable<T,add_lvalue_reference_t<add_const_t<T>>>
    {};

    template <typename T>
    constexpr inline auto is_copy_assignable_v = is_copy_assignable<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_COPY_ASSIGNABLE_HPP