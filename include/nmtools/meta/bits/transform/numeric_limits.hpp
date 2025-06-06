#ifndef NMTOOLS_META_BITS_TRANSFORM_NUMERIC_LIMITS_HPP
#define NMTOOLS_META_BITS_TRANSFORM_NUMERIC_LIMITS_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_signed.hpp"
#include "nmtools/def.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct numeric_limits
    {
        static constexpr T min()
        {
            if constexpr (is_signed_v<T>) {
                constexpr auto num_bits = sizeof(T) * 8;
                return (1U << (num_bits - 1));
            } else {
                return 0;
            }
        }

        static constexpr T max()
        {
            constexpr auto t_size = sizeof(T);
            if constexpr (!is_signed_v<T>) {
                if constexpr (t_size == 1) {
                    return 0xFF;
                } else if constexpr (t_size == 2) {
                    return 0xFFFF;
                } else if constexpr (t_size == 4) {
                    return 0xFFFFFFFF;
                } else if constexpr (t_size == 8) {
                    return 0xFFFFFFFFFFFFFFFF;
                }
            } else {
                if constexpr (t_size == 1) {
                    return 0x7F;
                } else if constexpr (t_size == 2) {
                    return 0x7FFF;
                } else if constexpr (t_size == 4) {
                    return 0x7FFFFFFF;
                } else if constexpr (t_size == 8) {
                    return 0x7FFFFFFFFFFFFFFF;
                }
            }
        }
    };

    template <>
    struct numeric_limits<float>
    {
        static constexpr auto min()
        {
            return -__builtin_huge_val();
        }

        static constexpr auto max()
        {
            return __builtin_huge_valf();
        }
    };

    template <>
    struct numeric_limits<double>
    {
        static constexpr auto min()
        {
            return -__builtin_huge_val();
        }

        static constexpr auto max()
        {
            return __builtin_huge_valf();
        }
    };

    template <typename T>
    struct numeric_limits<const T> : numeric_limits<T> {};
    template <typename T>
    struct numeric_limits<T&> : numeric_limits<T> {};

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_NUMERIC_LIMITS_HPP