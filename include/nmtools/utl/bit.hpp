#ifndef NMTOOLS_UTL_BIT_HPP
#define NMTOOLS_UTL_BIT_HPP

#define nmtools_bit_cast(T,x) \
(__builtin_bit_cast(T,x))

#define nmtools_bit_cast_constexpr constexpr
#define nmtools_has_constexpr_bit_cast (1)

// in clang, at least 20.x, __GNUC__ is defined to 4 when the gcc version is 14
// so skip in clang
#if defined(__GNUC__) && !defined(__clang__)
#if __GNUC__ < 10
// #define STR(x) #x
// #define XSTR(x) STR(x)
// #pragma message("Compiling with GCC Version: " XSTR(__GNUC__) "." XSTR(__GNUC_MINOR__) "." XSTR(__GNUC_PATCHLEVEL__))
// #pragma message "disabling some utl math constexpr"

#undef nmtools_bit_cast
#undef nmtools_bit_cast_constexpr
#undef nmtools_has_constexpr_bit_cast
#define nmtools_bit_cast(T,x) \
(*(T*)&x)
#define nmtools_bit_cast_constexpr
#define nmtools_has_constexpr_bit_cast (0)
#endif // __GNUC__ < 10
#endif // __GNUC__

namespace nmtools::utl
{
    template <typename to_t, typename from_t>
    nmtools_bit_cast_constexpr
    auto bit_cast(const from_t& from) -> to_t
    {
        return nmtools_bit_cast(to_t,from);
    }
}

#endif // NMTOOLS_UTL_BIT_HPP