#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_BIAS_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_BIAS_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct get_bias;

    template <>
    struct get_bias<float>
    {
        static constexpr auto value = 127;
    };

    template <>
    struct get_bias<double>
    {
        static constexpr auto value = 1023;
    };


    template <typename T>
    constexpr inline auto get_bias_v = get_bias<T>::value;
}

namespace nmtools
{
    using meta::get_bias_v;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_BIAS_HPP