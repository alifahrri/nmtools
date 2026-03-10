#ifndef NMTOOLS_UTL_FMATH_HPP
#define NMTOOLS_UTL_FMATH_HPP

#include "nmtools/utl/tuple.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"

namespace nmtools::utl
{
    template <typename T>
    constexpr inline T pi_v = 3.141592653589793238462643383279502884197;

    template <typename T>
    constexpr inline T ln2_v = 0.6931471805599453;

    template <typename T>
    constexpr inline T e_v = 2.718281828459045;

    template <typename T>
    constexpr inline T inv_ln2_v = 1.4426950408889634;

    template <typename T>
    constexpr inline T inv_ln10_v = 0.4342944819032518;

    template <typename T>
    constexpr auto abs(T t)
    {
        if (t < 0) {
            return -t;
        } else {
            return t;
        }
    }

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

    template <typename T>
    nmtools_bit_cast_constexpr
    auto get_exponent_bits(T x)
    {
        // TODO: handle double precision
        uint32_t bits = nmtools_bit_cast(uint32_t,x);

        auto shifted_bits = bits >> 23;

        auto exponent_field = shifted_bits & 0xFF;

        int32_t actual_exponent = exponent_field - 127;

        return actual_exponent;
    }

    template <typename T>
    nmtools_bit_cast_constexpr
    auto copy_sign(T x, T y)
    {
        // TODO: handle double precision
        auto x_bits = nmtools_bit_cast(uint32_t,x);
        auto y_bits = nmtools_bit_cast(uint32_t,y);

        auto sign_mask = 0x80000000;

        auto mag_x = x_bits & (~sign_mask);
        auto sgn_y = y_bits & sign_mask;

        auto result_bits = mag_x | sgn_y;

        return nmtools_bit_cast(T,result_bits);
    }

    template <typename exponent_t>
    constexpr auto create_integer_mask(exponent_t exponent)
    {
        // TODO: handle double precision
        // TODO: assert constant index
        if (exponent >= 23) {
            return 0xFFFFFFFF;
        }
        if (exponent < 0) {
            return 0x80000000;
        }

        int32_t num_fractional_bits = 23 - exponent;
        auto mask = 0xFFFFFFFF << num_fractional_bits;

        return mask;
    }

    template <typename T, typename U>
    nmtools_bit_cast_constexpr
    auto bitwise_and(T x, U mask)
    {
        // TODO: handle double precision
        auto bits = nmtools_bit_cast(uint32_t,x);

        auto masked_bits = bits & mask;

        return nmtools_bit_cast(T,masked_bits);
    }

    template <typename T>
    constexpr auto trunc(T x)
    {
        auto exponent = get_exponent_bits(x);

        // TODO: handle double precision
        if (exponent >= 23) {
            return x;
        }

        if ((int32_t)exponent < 0) {
            return copy_sign(T(0), x);
        }

        auto mask = create_integer_mask(exponent);
        auto result = bitwise_and(x,mask);

        return result;
    }

    template <typename T>
    constexpr auto floor(T x)
    {
        // int32 is enough for both float64 and float32 (?)
        // assume float, so use int
        // TODO: infer type
        int32_t i = x;
        if (x < i) {
            return (T)(i-1);
        } else {
            return (T)i;
        }
    }

    template <typename T>
    constexpr auto ceil(T x)
    {
        // int32 is enough for both float64 and float32 (?)
        // assume float, use int
        // TODO: infer type
        int32_t i = x;
        if (x > i) {
            return (T)(i + 1);
        } else {
            return (T)i;
        }
    }

    template <typename T>
    constexpr auto round(T x)
    {
        return (x >= 0) ? floor(x + T(0.5)) : ceil(x - T(0.5));
    }

    template <typename T, typename U>
    constexpr auto fmod(T x, U y)
    {
        // TODO: hanle nan
        // if (y == 0) {
        //     return T(NAN);
        // }
        auto quotient = trunc(T(x / y));

        auto result = x - (quotient * y);
        return result;
    }

    template <typename T>
    constexpr auto frexp(T num, int32_t* exp)
    {
        // TODO: generalize to another floating point
        using uint_t = conditional_t<
            (sizeof(T) == (64/8)),
            uint64_t,
            uint32_t
        >;

        union {
            T f;
            uint_t i;
        } u;

        u.f = num;

        if (num == T(0)) {
            if (exp) {
                *exp = 0;
            }
            return T(0);
        }

        constexpr auto mantissa_shift = ((sizeof(T) == (64/8)) ? 52 : 23);
        constexpr auto mask = ((sizeof(T) == (64/8)) ? 0x7FFull : 0xFF);

        int raw_exp = (u.i >> mantissa_shift) & mask;

        // check if inf or nan
        if (raw_exp == mask) {
            *exp = 0;
            return num;
        }

        if (exp) {
            constexpr auto bias = ((sizeof(T) == (64/8)) ? 1022 : 126);
            *exp = raw_exp - bias;
        }

        constexpr auto exp_mask = ((sizeof(T) == (64/8)) ? 0x7FF0000000000000ull : 0x7F800000u);
        u.i &= ~exp_mask;
        constexpr auto raw_exp_mask = ((sizeof(T) == (64/8)) ? (0x3FEull << 52) : (0x7Eu << 23));
        u.i |= (raw_exp_mask);

        return u.f;
    }

    template <typename T>
    nmtools_bit_cast_constexpr
    auto ldexp(T x, int32_t exp)
    {
        // TODO: check for isnan and isinf
        if (x == T(0) || exp == 0) {
            return x;
        }

        using int_t = conditional_t<
            sizeof(T)==(64/8)
            , uint64_t
            , uint32_t
        >;

        int_t bits = nmtools_bit_cast(int_t,x);

        constexpr auto mantissa_shift = ((sizeof(T) == (64/8)) ? 52 : 23);
        constexpr auto mask = ((sizeof(T) == (64/8)) ? 0x7FFull : 0xFF);

        int32_t current_exp = (bits >> mantissa_shift) & mask;
        int32_t new_exp = current_exp + exp;

        // TODO: handle overflow and underflow

        bits &= ~(mask << mantissa_shift);
        bits |= (static_cast<int_t>(new_exp) << mantissa_shift);

        return nmtools_bit_cast(T,bits);
    }

    template <typename T>
    constexpr auto frexp(T num)
    {
        int32_t e = {};
        auto m = frexp(num,&e);
        return utl::tuple{m,e};
    }

    template <typename T, typename U=float>
    constexpr auto sqrt(T x, U tol=U{1e-7}, nm_size_t max_iter=25)
    {
        // zero
        if (abs(x) < tol) {
            return x;
        }
        T guess = x / T(2);

        for (nm_size_t i=0; (i<max_iter); i++) {
            auto next_guess = T(0.5) * (guess + (x/guess));

            auto done = abs(guess - next_guess) < tol;
            guess = next_guess;

            if (done) {
                break;
            }
        }
        return guess;
    }

    // TODO: generalize pow
    template <typename T>
    constexpr auto pow(T t, nm_size_t k)
    {
        auto res = T{1};
        for (nm_size_t i=0; i<k; i++) {
            res = res * t;
        }
        return res;
    }
}

#endif // NMTOOLS_UTL_FMATH_HPP