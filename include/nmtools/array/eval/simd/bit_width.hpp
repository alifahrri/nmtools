#ifndef NMTOOLS_ARRAY_EVAL_SIMD_BIT_WIDTH_HPP
#define NMTOOLS_ARRAY_EVAL_SIMD_BIT_WIDTH_HPP

#include "nmtools/meta.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct BIT_WIDTH_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T>
    struct bit_width
    {
        static constexpr auto value = error::BIT_WIDTH_UNSUPPORTED<T>{};
    };

    template <typename T>
    constexpr inline auto bit_width_v = bit_width<T>::value;
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_EVAL_SIMD_BIT_WIDTH_HPP