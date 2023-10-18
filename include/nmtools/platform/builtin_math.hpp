#ifndef NMTOOLS_PLATFORM_BUILTIN_MATH_HPP
#define NMTOOLS_PLATFORM_BUILTIN_MATH_HPP

// See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html

#ifndef nmtools_builtin_sqrtf
#define nmtools_builtin_sqrtf(x) __builtin_sqrtf(x)
#endif

#ifndef nmtools_builtin_sqrt
#define nmtools_builtin_sqrt(x) __builtin_sqrt(x)
#endif

#ifndef nmtools_builtin_floorf
#define nmtools_builtin_floorf(x) __builtin_floorf(x)
#endif

#ifndef nmtools_builtin_floor
#define nmtools_builtin_floor(x) __builtin_floor(x)
#endif

#ifndef nmtools_builtin_ceilf
#define nmtools_builtin_ceilf(x) __builtin_ceilf(x)
#endif

#ifndef nmtools_builtin_ceil
#define nmtools_builtin_ceil(x) __builtin_ceil(x)
#endif

#ifndef nmtools_builtin_fmaxf
#define nmtools_builtin_fmaxf(x,y) __builtin_fmaxf(x,y)
#endif

#ifndef nmtools_builtin_fmax
#define nmtools_builtin_fmax(x,y) __builtin_fmax(x,y)
#endif

#ifndef nmtools_builtin_fminf
#define nmtools_builtin_fminf(x,y) __builtin_fminf(x,y)
#endif

#ifndef nmtools_builtin_fmin
#define nmtools_builtin_fmin(x,y) __builtin_fmin(x,y)
#endif

#endif // NMTOOLS_PLATFORM_BUILTIN_MATH_HPP