#ifndef NMTOOLS_META_BUILTINS_HPP
#define NMTOOLS_META_BUILTINS_HPP

// type-related compiler builtins
// for example from https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gcc/Type-Traits.html
// but seems like also working with clang

#if defined(__GNUC__) || defined(__clang__)

#ifdef __clang_major__
#if __clang_major__ >= 15
#define NMTOOLS_IS_TRIVIALLY_DESTRUCTIBLE __is_trivially_destructible
#endif
#endif

#define NMTOOLS_HAS_TRIVIAL_DESTRUCTOR  __has_trivial_destructor
#define NMTOOLS_HAS_TRIVIAL_COPY        __has_trivial_copy
#define NMTOOLS_HAS_TRIVIAL_CONSTRUCTOR __has_trivial_constructor

#define NMTOOLS_IS_BASE_OF __is_base_of
#define NMTOOLS_IS_UNION   __is_union
#define NMTOOLS_IS_POD     __is_pod

#endif

// borrow std type traits, may not exist on embedded or gpgpu
#if __has_include(<type_traits>)

#include <type_traits>
#define NMTOOLS_IS_TRIVIALLY_CONSTRUCTIBLE(...) (std::is_trivially_constructible_v<__VA_ARGS__>)

// TODO: check if compiler builtins is not available (maybe on msvc?), then use stl if possible

#endif

#endif // NMTOOLS_META_BUILTINS_HPP