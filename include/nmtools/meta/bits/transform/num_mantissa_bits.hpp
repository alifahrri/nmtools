#ifndef NMTOOLS_META_BITS_TRANSFOMR_NUM_MANTISSA_BITS_HPP
#define NMTOOLS_META_BITS_TRANSFOMR_NUM_MANTISSA_BITS_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct num_mantissa_bits;

    template <>
    struct num_mantissa_bits<float>
    {
        static constexpr auto value = 23;
    };

    template <>
    struct num_mantissa_bits<double>
    {
        static constexpr auto value = 52;
    };

    template <typename T>
    constexpr inline auto num_mantissa_bits_v = num_mantissa_bits<T>::value;
}

namespace nmtools
{
    using meta::num_mantissa_bits_v;
}

#endif // NMTOOLS_META_BITS_TRANSFOMR_NUM_MANTISSA_BITS_HPP