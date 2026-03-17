#ifndef NMTOOLS_UTL_POWER_HPP
#define NMTOOLS_UTL_POWER_HPP

#include "nmtools/utl/fmath.hpp"

namespace nmtools::utl
{
    template <typename T>
    constexpr auto cos_maclaurin(T x, nm_size_t num_terms=10)
    {
        auto mod = [](auto x, auto y){
            return x - utl::floor(x/y) * y;
        };
        x = mod(x+pi_v<T>,(2*pi_v<T>)) - pi_v<T>;

        T result = 1;
        T term = 1;

        auto x_squared = x * x;

        for (nm_size_t i=1; i<num_terms; i++) {
            auto denominator = (2*i) * (2*i-1);

            term = term * (-x_squared) / denominator;

            result += term;
        }

        return result;
    }

    template <typename T>
    constexpr auto sin_maclaurin(T x, nm_size_t num_terms=10)
    {
        auto mod = [](auto x, auto y){
            return x - utl::floor(x/y) * y;
        };
        x = mod(x+pi_v<T>,(2*pi_v<T>)) - pi_v<T>;

        auto result = x;
        auto term = x;

        auto x_squared = x * x;

        for (nm_size_t n=1; n<num_terms; n++) {
            auto denominator = ((2*n)*(2*n+1));
            term = term * (-x_squared) / denominator;

            result = result + term;
        }

        return result;
    }

    template <typename T>
    constexpr auto log_maclaurin(T x, nm_size_t num_terms=25)
    {
        x = utl::abs(x);

        T sum = 1;
        auto term = x;

        for (nm_size_t i=1; i<=num_terms; i++) {
            auto denominator = (2*i) + 1;
            sum += term / denominator;
            term *= x;
        }

        return sum;
    }

    template <typename T>
    constexpr auto exp2_maclaurin(T x, nm_size_t num_terms=15)
    {
        T k = utl::round(x);
        T r = x - k;

        T z = r * ln2_v<T>;

        T result = 1;
        T term = 1;

        for (nm_size_t i=1; i<=num_terms; i++) {
            term = term * z / i;
            result += term;
        }

        return utl::ldexp(result,k);
    }

    template <typename T>
    constexpr auto exp2_pade(T x)
    {
        T k = utl::round(x);
        T r = x - k;

        T z = r * ln2_v<T>;
        T z2 = z * z;
        T z3 = z2 * z;

        T P = T(1) + (z / T(2)) + (z2 / T(10)) + (z3 / T(120));
        T Q = T(1) - (z / T(2)) + (z2 / T(10)) - (z3 / T(120));

        return utl::ldexp(P/Q,k);
    }
}

#endif // NMTOOLS_UTL_POWER_HPP