#ifndef NMTOOLS_UTL_FMATH_HPP
#define NMTOOLS_UTL_FMATH_HPP

#include "nmtools/utl/tuple.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct num_exponent_bits;

    template <typename T>
    struct num_mantissa_bits;

    template <typename T>
    struct get_bias;

    template <nm_size_t bits>
    struct get_uint;

    /********************************************************************* */

    template <>
    struct num_exponent_bits<float>
    {
        static constexpr auto value = 8;
    };

    template <>
    struct num_mantissa_bits<float>
    {
        static constexpr auto value = 23;
    };

    template <>
    struct get_bias<float>
    {
        static constexpr auto value = 127;
    };

    template <>
    struct get_uint<32>
    {
        using type = uint32_t;
    };

    /********************************************************************* */

    template <>
    struct num_exponent_bits<double>
    {
        static constexpr auto value = 11;
    };

    template <>
    struct num_mantissa_bits<double>
    {
        static constexpr auto value = 52;
    };

    template <>
    struct get_bias<double>
    {
        static constexpr auto value = 1023;
    };

    template <>
    struct get_uint<64>
    {
        using type = uint64_t;
    };
    
    /********************************************************************* */

    #ifdef NMTOOLS_HAS_FLOAT16

    template <>
    struct num_exponent_bits<float16_t>
    {
        static constexpr auto value = 5;
    };

    template <>
    struct num_mantissa_bits<float16_t>
    {
        static constexpr auto value = 10;
    };

    template <>
    struct get_bias<float16_t>
    {
        static constexpr auto value = 15;
    };

    template<>
    struct get_uint<16>
    {
        using type = uint16_t;
    };

    #endif // NMTOOLS_HAS_FLOAT16

    /********************************************************************* */

    template <typename T>
    constexpr inline auto num_exponent_bits_v = num_exponent_bits<T>::value;

    template <typename T>
    constexpr inline auto num_mantissa_bits_v = num_mantissa_bits<T>::value;

    template <typename T>
    constexpr inline auto get_bias_v = get_bias<T>::value;

    template <auto bits>
    using get_uint_t = type_t<get_uint<bits>>;
}

namespace nmtools
{
    using meta::num_exponent_bits_v;
    using meta::num_mantissa_bits_v;
    using meta::get_bias_v;
    using meta::get_uint_t;
}

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
        using uint_t = get_uint_t<sizeof(T)*8>;
        uint_t bits = nmtools_bit_cast(uint_t,x);

        auto shifted_bits = bits >> num_mantissa_bits_v<T>;

        auto exponent_field = shifted_bits & ((2 << num_exponent_bits_v<T>) - 1);

        int32_t actual_exponent = exponent_field - get_bias_v<T>;

        return actual_exponent;
    }

    template <typename T>
    nmtools_bit_cast_constexpr
    auto signbit(T x)
    {
        using uint_t = get_uint_t<sizeof(T)*8>;

        uint_t bits = nmtools_bit_cast(uint_t,x);

        constexpr auto mantissa_shift = num_mantissa_bits_v<T>;
        constexpr auto mantissa_mask  = ((uint_t)1 << mantissa_shift) - 1;
        constexpr auto exponent_mask  = ((uint_t)1 << num_exponent_bits_v<T>) - 1;

        uint_t sign_bit = bits & ~(mantissa_mask | (exponent_mask << mantissa_shift));

        return static_cast<bool>(sign_bit);
    }

    template <typename T>
    nmtools_bit_cast_constexpr
    auto copy_sign(T x, T y)
    {
        using uint_t = get_uint_t<sizeof(T)*8>;
        auto x_bits = nmtools_bit_cast(uint_t,x);
        auto y_bits = nmtools_bit_cast(uint_t,y);

        auto sign_mask = ((uint_t)1 << ((sizeof(T)*8)-1));

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
        using uint_t = get_uint_t<sizeof(T)*8>;
        auto bits = nmtools_bit_cast(uint_t,x);

        auto masked_bits = bits & mask;

        return nmtools_bit_cast(T,masked_bits);
    }

    template <typename T>
    nmtools_bit_cast_constexpr
    auto ilogb(T x)
    {
        using uint_t = get_uint_t<sizeof(T)*8>;
        auto bits = nmtools_bit_cast(uint_t,x);

        constexpr auto mantissa_shift = num_mantissa_bits_v<T>;
        // constexpr auto mantissa_mask  = ((uint_t)1 << num_mantissa_bits_v<T>) - 1;
        constexpr auto exponent_mask  = ((uint_t)1 << num_exponent_bits_v<T>) - 1;

        // uint_t mantissa = bits & mantissa_mask;
        uint_t exp_bits = (bits >> mantissa_shift) & exponent_mask;

        // TODO: handle zero
        // TODO: handle infinity & nan
        // TODO: handle subnormals

        return static_cast<int32_t>(exp_bits) - get_bias_v<T>;
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

    template <typename T>
    constexpr auto frexp(T num, int32_t* exp)
    {
        using uint_t = get_uint_t<sizeof(T)*8>;

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

        constexpr auto mantissa_shift = num_mantissa_bits_v<T>;
        constexpr auto mantissa_mask  = ((uint_t)1 << mantissa_shift) - 1;
        constexpr auto exponent_mask  = ((uint_t)1 << num_exponent_bits_v<T>) - 1;

        int raw_exp = (u.i >> mantissa_shift) & exponent_mask;

        // check if inf or nan
        if (raw_exp == exponent_mask) {
            if (exp) {
                *exp = 0;
                return num;
            }
        }

        // TODO: handle subnormals

        if (exp) {
            *exp = raw_exp - get_bias_v<T> + 1;
        }
        uint_t new_exp_bits = get_bias_v<T> - 1;
        uint_t mantissa = u.i & mantissa_mask;
        uint_t sign_bit = u.i & ~(mantissa_mask | (exponent_mask << mantissa_shift));
        u.i = sign_bit | (new_exp_bits << num_mantissa_bits_v<T>) | mantissa;

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

        using uint_t = get_uint_t<sizeof(T)*8>;

        uint_t bits = nmtools_bit_cast(uint_t,x);

        constexpr auto mantissa_shift = num_mantissa_bits_v<T>;
        constexpr auto mask = ((uint_t)1 << num_exponent_bits_v<T>) - 1;

        int32_t current_exp = (bits >> mantissa_shift) & mask;
        int32_t new_exp = current_exp + exp;

        // TODO: handle inf / nan
        // TODO: handle subnormals
        // TODO: handle overflow and underflow

        bits &= ~(mask << mantissa_shift);
        bits |= (static_cast<uint_t>(new_exp) << mantissa_shift);

        return nmtools_bit_cast(T,bits);
    }

    template <typename T>
    constexpr auto frexp(T num)
    {
        int32_t e = {};
        auto m = utl::frexp(num,&e);
        return utl::tuple{m,e};
    }

    #if 0
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
    #else
    template <typename T>
    nmtools_bit_cast_constexpr
    auto fmod(T x, T y)
    {
        // TODO: handle case when y = 0 or x is nan/inf: return quiet nan
        // TODO: handle case when y is inf/nan: return x

        auto is_negative = utl::signbit(x);
        x = utl::abs(x);
        y = utl::abs(y);

        if (x < y) {
            return is_negative ? -x : x;
        }
        if (x == y) {
            return is_negative ? -T(0) : T(0);
        }

        auto exp_x = utl::ilogb(x);
        auto exp_y = utl::ilogb(y);
        int n = exp_x - exp_y;

        auto scaled_y = utl::ldexp(y,n);

        for (int i=0; i<=n; i++) {
            if (x >= scaled_y) {
                x -= scaled_y;
            }
            scaled_y *= T(0.5);
        }

        return is_negative ? -x : x;
    }
    #endif

    template <typename T>
    nmtools_bit_cast_constexpr
    auto remainder(T x, T y)
    {
        // TODO: handle if y = 0 or x is nan/inf
        // TODO: handle if y is nan/inf or x = 0

        auto is_negative = utl::signbit(x);

        x = utl::abs(x);
        y = utl::abs(y);

        auto half_y = y / 2;

        if (x < half_y) {
            return is_negative ? -x : x;
        }

        auto exp_x = utl::ilogb(x);
        auto exp_y = utl::ilogb(y);
        auto n = exp_x - exp_y;

        int parity = 0;
        auto scaled_y = utl::ldexp(y,n);

        for (int i=n; i>=0; i--) {
            if (x >= scaled_y) {
                x -= scaled_y;
                if (i == 0) {
                    parity = 1;
                }
            }
            scaled_y /= 2;
        }

        if (x > half_y) {
            x -= y;
        } else if (x == half_y && parity) {
            x -= y;
        }

        return is_negative ? -x : x;
    }

    template <typename T, typename U=float>
    constexpr auto sqrt(T x, U tol=U{1e-16}, nm_size_t max_iter=25)
    {
        // zero
        if (abs(x) < tol) {
            return x;
        }
        T guess = x * T(0.5);

        for (nm_size_t i=0; (i<max_iter); i++) {
            auto next_guess = T(0.5) * (guess + (x/guess));

            auto done = utl::abs(guess - next_guess) < tol;
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