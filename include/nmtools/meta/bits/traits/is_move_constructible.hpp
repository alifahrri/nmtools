#ifndef NMTOOLS_META_BITS_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/add_reference.hpp"
#include "nmtools/meta/bits/traits/is_constructible.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct is_move_constructible
        : is_constructible<T,add_rvalue_reference_t<T>>
    {};

    template <typename T>
    constexpr inline auto is_move_constructible_v = is_move_constructible<T>::value;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP