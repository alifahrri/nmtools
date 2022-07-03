#ifndef NMTOOLS_META_BUILTINS_HPP
#define NMTOOLS_META_BUILTINS_HPP

// type-related compiler builtins
// for example from https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gcc/Type-Traits.html
// but seems like also working with clang

#if defined(__GNUC__) || defined(__clang__)

#define NMTOOLS_HAS_TRIVIAL_DESTRUCTOR __has_trivial_destructor

#define NMTOOLS_IS_BASE_OF __is_base_of
#define NMTOOLS_IS_UNION   __is_union
#define NMTOOLS_IS_POD     __is_pod

#endif

#endif // NMTOOLS_META_BUILTINS_HPP