#ifndef NMTOOLS_PLATFORM_CUDA_MATH_HPP
#define NMTOOLS_PLATFORM_CUDA_MATH_HPP

#if defined(__CUDA__) && defined(__CUDA_ARCH__)
// compiling cuda kernel
// under math namespace to not collide with array/ufunc
namespace nmtools::math
{

#define NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(fn) \
    template <typename T> \
    __host__ __device__ auto fn(T t) { return ::fn##f(t); } \
    __host__ __device__ auto fn(double t) { return ::fn(t); }

#define NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(fn) \
    template <typename T, typename U> \
    __host__ __device__ auto fn(T t, U u) { return ::fn##f(t,u); } \
    __host__ __device__ auto fn(double t, double u) { return ::fn(t,u); }

#define NMTOOLS_UNARY_MATH_FWD_CUDA_STL(fn) \
    template <typename T> \
    constexpr auto fn(T t) \
    { return ::fn(t); }

#define NMTOOLS_BINARY_MATH_FWD_CUDA_STL(fn) \
    template <typename T, typename U> \
    constexpr auto fn(T t, U u) \
    { return ::fn(t,u); }

    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(exp)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(log)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(cos)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(sin)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(tan)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(cosh)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(sinh)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(tanh)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(exp2)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(acos)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(asin)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(atan)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(fabs)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(rint)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(log2)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(sqrt)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(cbrt)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(ceil)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(trunc)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(floor)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(atanh)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(acosh)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(asinh)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(expm1)

    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(log1p)
    NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL(log10)

    NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(pow)
    NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(fmax)
    NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(fmin)
    NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(fmod)
    NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(atan2)
    NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(hypot)
    NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL(ldexp)

    NMTOOLS_UNARY_MATH_FWD_CUDA_STL(isinf)
    NMTOOLS_UNARY_MATH_FWD_CUDA_STL(isnan)
    NMTOOLS_UNARY_MATH_FWD_CUDA_STL(isfinite)
    NMTOOLS_UNARY_MATH_FWD_CUDA_STL(signbit)

    NMTOOLS_BINARY_MATH_FWD_CUDA_STL(max)
    NMTOOLS_BINARY_MATH_FWD_CUDA_STL(min)

#undef NMTOOLS_UNARY_MATH_FWD_CUDA_KERNEL
#undef NMTOOLS_BINARY_MATH_FWD_CUDA_KERNEL
#undef NMTOOLS_UNARY_MATH_FWD_CUDA_STL
#undef NMTOOLS_BINARY_MATH_FWD_CUDA_STL
}
#else
#include "nmtools/platform/math/stl.hpp"
#endif

#endif // NMTOOLS_PLATFORM_CUDA_MATH_HPP