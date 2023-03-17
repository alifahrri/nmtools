#ifndef NMTOOLS_META_BITS_TRANSFORM_CONDITIONAL_HPP
#define NMTOOLS_META_BITS_TRANSFORM_CONDITIONAL_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <bool condition, typename true_t, typename false_t>
    struct conditional;

    template <typename true_t, typename false_t>
    struct conditional<true,true_t,false_t>
    {
        using type = true_t;
    };

    template <typename true_t, typename false_t>
    struct conditional<false,true_t,false_t>
    {
        using type = false_t;
    };

    template <bool C, typename T, typename F>
    using conditional_t = type_t<conditional<C,T,F>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_CONDITIONAL_HPP