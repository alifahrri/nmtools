#ifndef NMTOOLS_META_BITS_TRANSFORM_NUM_EXPONENT_BITS_HPP
#define NMTOOLS_META_BITS_TRANSFORM_NUM_EXPONENT_BITS_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct num_exponent_bits;

    template <>
    struct num_exponent_bits<float>
    {
        static constexpr auto value = 8;
    };

    template <>
    struct num_exponent_bits<double>
    {
        static constexpr auto value = 11;
    };

    template <typename T>
    constexpr inline auto num_exponent_bits_v = num_exponent_bits<T>::value;
}

namespace nmtools
{
    using meta::num_exponent_bits_v;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_NUM_EXPONENT_BITS_HPP