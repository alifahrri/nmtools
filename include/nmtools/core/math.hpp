#ifndef NMTOOLS_CORE_MATH_HPP
#define NMTOOLS_CORE_MATH_HPP

#include "nmtools/utl/math.hpp"
#include "nmtools/math.hpp"

// math ops

// TODO: rename this to math, and rename existing math to platform::math
namespace nmtools::ops
{
    #define NMTOOLS_MATH_UNARY(fn) \
    struct fn##_t \
    { \
        template <typename T> \
        constexpr auto operator()(const T x) const \
        { \
            return nmtools::math::fn(x); \
        } \
    }; \
    constexpr inline auto fn = fn##_t{};

    #define NMTOOLS_MATH_BINARY(fn) \
    struct fn##_t \
    { \
        template <typename T, typename U> \
        constexpr auto operator()(const T x, const U y) const \
        { \
            return nmtools::math::fn(x,y); \
        } \
    }; \
    constexpr inline auto fn = fn##_t{};

    NMTOOLS_MATH_UNARY(exp)
    NMTOOLS_MATH_UNARY(log)
    NMTOOLS_MATH_UNARY(cos)
    NMTOOLS_MATH_UNARY(sin)
    NMTOOLS_MATH_UNARY(tan)
    NMTOOLS_MATH_UNARY(cosh)
    NMTOOLS_MATH_UNARY(sinh)
    NMTOOLS_MATH_UNARY(tanh)
    NMTOOLS_MATH_UNARY(exp2)
    NMTOOLS_MATH_UNARY(acos)
    NMTOOLS_MATH_UNARY(asin)
    NMTOOLS_MATH_UNARY(atan)
    NMTOOLS_MATH_UNARY(fabs)
    NMTOOLS_MATH_UNARY(rint)
    NMTOOLS_MATH_UNARY(log2)
    NMTOOLS_MATH_UNARY(sqrt)
    NMTOOLS_MATH_UNARY(cbrt)
    NMTOOLS_MATH_UNARY(ceil)
    NMTOOLS_MATH_UNARY(trunc)
    NMTOOLS_MATH_UNARY(floor)
    NMTOOLS_MATH_UNARY(atanh)
    NMTOOLS_MATH_UNARY(acosh)
    NMTOOLS_MATH_UNARY(asinh)
    NMTOOLS_MATH_UNARY(expm1)
    NMTOOLS_MATH_UNARY(isinf)
    NMTOOLS_MATH_UNARY(isnan)
    NMTOOLS_MATH_UNARY(log1p)
    NMTOOLS_MATH_UNARY(log10)
    NMTOOLS_MATH_UNARY(signbit)
    NMTOOLS_MATH_UNARY(isfinite)

    NMTOOLS_MATH_BINARY(max)
    NMTOOLS_MATH_BINARY(min)
    NMTOOLS_MATH_BINARY(pow)
    NMTOOLS_MATH_BINARY(fmax)
    NMTOOLS_MATH_BINARY(fmin)
    NMTOOLS_MATH_BINARY(fmod)
    NMTOOLS_MATH_BINARY(atan2)
    NMTOOLS_MATH_BINARY(hypot)
    NMTOOLS_MATH_BINARY(ldexp)

    #undef NMTOOLS_MATH_UNARY
    #undef NMTOOLS_MATH_BINARY
}

namespace nmtools::ops::utl
{
    #define NMTOOLS_UTL_MATH_UNARY(fn) \
    struct fn##_t \
    { \
        template <typename T> \
        constexpr auto operator()(const T x) const \
        { \
            return nmtools::utl::fn(x); \
        } \
    }; \
    constexpr inline auto fn = fn##_t{};

    #define NMTOOLS_UTL_MATH_BINARY(fn) \
    struct fn##_t \
    { \
        template <typename T, typename U> \
        constexpr auto operator()(const T x, const U y) const \
        { \
            return nmtools::utl::fn(x,y); \
        } \
    }; \
    constexpr inline auto fn = fn##_t{};

    NMTOOLS_UTL_MATH_UNARY(cos)
    NMTOOLS_UTL_MATH_UNARY(sin)
    NMTOOLS_UTL_MATH_UNARY(exp)
    NMTOOLS_UTL_MATH_UNARY(exp2)
    NMTOOLS_UTL_MATH_UNARY(log)
    NMTOOLS_UTL_MATH_UNARY(log2)
    NMTOOLS_UTL_MATH_UNARY(log10)

    #undef NMTOOLS_UTL_MATH_UNARY
    #undef NMTOOLS_UTL_MATH_BINARY
}

#endif // NMTOOLS_CORE_MATH_HPP