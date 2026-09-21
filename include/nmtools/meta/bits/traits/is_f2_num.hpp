#ifndef NMTOOLS_META_BITS_TRAITS_IS_F2_NUM_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_F2_NUM_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"

namespace nmtools::meta
{
    // add "num" to be clear f2 is a number system
    template <typename T>
    struct is_f2_num : false_type {};

    template <typename T>
    constexpr inline auto is_f2_num_v = is_f2_num<T>::value;
}

namespace nmtools
{
    using meta::is_f2_num_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_F2_NUM_HPP