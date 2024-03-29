#ifndef NMTOOLS_PLATFORM_MATH_ARDUINO_HPP
#define NMTOOLS_PLATFORM_MATH_ARDUINO_HPP

#include <math.h>

// under math namespace to not collide with array/ufunc
namespace nmtools::math
{

#define NMTOOLS_UNARY_MATH_FWD_ARDUINO(fn) \
    template <typename T> \
    constexpr auto fn(T t) \
    { return ::fn(t); }

#define NMTOOLS_BINARY_MATH_FWD_ARDUINO(fn) \
    template <typename T, typename U> \
    constexpr auto fn(T t, U u) \
    { return ::fn(t,u); }

    NMTOOLS_UNARY_MATH_FWD_ARDUINO(exp)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(log)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(cos)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(sin)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(tan)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(cosh)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(sinh)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(tanh)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(acos)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(asin)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(atan)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(fabs)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(sqrt)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(cbrt)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(ceil)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(trunc)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(floor)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(isinf)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(isnan)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(log10)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(signbit)
    NMTOOLS_UNARY_MATH_FWD_ARDUINO(isfinite)

    NMTOOLS_BINARY_MATH_FWD_ARDUINO(pow)
    NMTOOLS_BINARY_MATH_FWD_ARDUINO(fmax)
    NMTOOLS_BINARY_MATH_FWD_ARDUINO(fmin)
    NMTOOLS_BINARY_MATH_FWD_ARDUINO(fmod)
    NMTOOLS_BINARY_MATH_FWD_ARDUINO(atan2)
    NMTOOLS_BINARY_MATH_FWD_ARDUINO(hypot)
    NMTOOLS_BINARY_MATH_FWD_ARDUINO(ldexp)

    // The following functions are not available on the smallest device (uno)

    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(exp2)
    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(rint)
    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(log2)
    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(atanh)
    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(acosh)
    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(asinh)
    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(expm1)
    // NMTOOLS_UNARY_MATH_FWD_ARDUINO(log1p)
    // NMTOOLS_BINARY_MATH_FWD_ARDUINO(max)
    // NMTOOLS_BINARY_MATH_FWD_ARDUINO(min)

#undef NMTOOLS_UNARY_MATH_FWD_ARDUINO
#undef NMTOOLS_BINARY_MATH_FWD_ARDUINO
}

#endif // NMTOOLS_PLATFORM_MATH_ARDUINO_HPP