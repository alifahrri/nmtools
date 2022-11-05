#ifndef NMTOOLS_PLATFORM_MATH_CONSTEXPR_HPP
#define NMTOOLS_PLATFORM_MATH_CONSTEXPR_HPP

// workaround for constexpr math

namespace nmtools::math
{
    template <typename Int=int, typename Float>
    constexpr Int constexpr_ceil(Float f)
    {
        const auto i = static_cast<Int>(f);
        return f > i ? i + 1 : i;
    }

    template <typename Int=int, typename Float>
    constexpr Int constexpr_floor(Float f)
    {
        const auto i = static_cast<Int>(f);
        return f < i ? i - 1 : i;
    }

    template <typename Float=float, typename T>
    constexpr Float constexpr_fabs(T t)
    {
        return (t < 0 ? -t : t);
    }
}

#endif // NMTOOLS_PLATFORM_MATH_CONSTEXPR_HPP