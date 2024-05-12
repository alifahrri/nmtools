#ifndef NMTOOLS_META_BUILTINS_HPP
#define NMTOOLS_META_BUILTINS_HPP

// type-related compiler builtins
// for example from https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gcc/Type-Traits.html
// but seems like also working with clang

#if defined(__GNUC__) || defined(__clang__)

// avoid clang deprecation
#ifdef __clang_major__
#if __clang_major__ >= 15
#define NMTOOLS_HAS_TRIVIAL_CONSTRUCTOR __is_trivially_constructible
#define NMTOOLS_HAS_TRIVIAL_DESTRUCTOR  __is_trivially_destructible
#define NMTOOLS_HAS_TRIVIAL_COPY        __is_trivially_copyable

// trivially constructible may accepts T,Args...
#define NMTOOLS_IS_TRIVIALLY_CONSTRUCTIBLE __is_trivially_constructible

#else // __clang_major__ >= 15
#define NMTOOLS_HAS_TRIVIAL_CONSTRUCTOR __has_trivial_constructor
#define NMTOOLS_HAS_TRIVIAL_DESTRUCTOR  __has_trivial_destructor
#define NMTOOLS_HAS_TRIVIAL_COPY        __has_trivial_copy
#endif // __clang_major__ >= 15
#endif

#define NMTOOLS_IS_BASE_OF __is_base_of
#define NMTOOLS_IS_UNION   __is_union
#define NMTOOLS_IS_POD     __is_pod

#endif

// borrow std type traits, may not exist on embedded or gpgpu
#if __has_include(<type_traits>)

#include <type_traits>
#if !defined(NMTOOLS_IS_TRIVIALLY_CONSTRUCTIBLE)
#define NMTOOLS_IS_TRIVIALLY_CONSTRUCTIBLE(...) (std::is_trivially_constructible_v<__VA_ARGS__>)
#endif
// Quick workaround since gcc doesn't have __is_trivally_destructible
#if !defined(NMTOOLS_IS_TRIVIALLY_DESTRUCTIBLE)
#define NMTOOLS_IS_TRIVIALLY_DESTRUCTIBLE(...) (std::is_trivially_destructible_v<__VA_ARGS__>)
#endif

// TODO: check if compiler builtins is not available (maybe on msvc?), then use stl if possible

#endif

#endif // NMTOOLS_META_BUILTINS_HPP