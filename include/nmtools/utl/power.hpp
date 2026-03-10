#ifndef NMTOOLS_UTL_POWER_HPP
#define NMTOOLS_UTL_POWER_HPP

#include "nmtools/utl/fmath.hpp"

namespace nmtools::utl
{
    // TODO: rename to cos taylor/maclaurin
    template <typename T>
    constexpr auto taylor_cos(T x, T precision_limit=1e-16, nm_size_t max_iter=100)
    {
        x = fmod(x,(2 * pi_v<T>));
        if (x > pi_v<T>) {
            x = x - (2 * pi_v<T>);
        }

        T result = 1;
        T term = 1;
        nm_size_t n = 1;

        auto x_squared = x * x;

        while (abs(term) > precision_limit) {
            auto multiplier = -x_squared / ((2*n-1)*(2*n));
            term = term * multiplier;

            result = result + term;
            n = n + 1;

            if (n > max_iter) {
                break;
            }
        }

        return result;
    }

    // TODO: rename to sin taylor/maclaurin
    template <typename T>
    constexpr auto taylor_sin(T x, T precision_limit=1e-16, nm_size_t max_iter=100)
    {
        x = fmod(x,(2 * pi_v<T>));
        if (x > pi_v<T>) {
            x = x - (2*pi_v<T>);
        } else if (x < -pi_v<T>) {
            x = x + (2*pi_v<T>);
        }

        auto result = x;
        auto term = x;
        nm_size_t n = 1;

        auto x_squared = x * x;

        while (abs(term) > precision_limit) {
            auto multiplier = -x_squared / ((2*n)*(2*n+1));
            term = term * multiplier;

            result = result + term;
            n = n + 1;

            if (n > max_iter) {
                break;
            }
        }

        return result;
    }

    // TODO: rename to exp taylor/maclaurin
    template <typename T>
    constexpr auto taylor_exp(T t, T precision_limit=1e-15, nm_size_t max_iter=100)
    {
        T result = 1;
        T term = 1;
        nm_size_t n = 1;

        while (abs(term) > precision_limit) {
            term = term * (t / n);
            result = result + term;
            n = n+1;

            if (n>max_iter) {
                break;
            }
        }

        return result;
    }

    template <typename T>
    constexpr auto log_series(T x, nm_size_t num_terms=10)
    {
        const auto [m_,e_] = utl::frexp(x);

        auto m = m_ * T(2);
        auto e = e_ - 1;

        auto z = (m - T(1)) / (m + 1);
        auto z_squared = z * z;

        T sum = 0;
        auto term = z;

        for (nm_size_t i=1; i<=num_terms; i++) {
            auto denominator = (2*i) - 1;
            sum += term / denominator;
            term *= z_squared;
        }

        T ln_m = 2 * sum;

        return ln_m + (e * ln2_v<T>);
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
    constexpr auto log2_series(T x, nm_size_t num_terms=10)
    {
        const auto [m_,e_] = utl::frexp(x);

        auto m = m_ * T(2);
        auto e = e_ - 1;

        auto z = (m - T(1)) / (m + 1);
        auto z_squared = z * z;

        T sum = 0;
        auto term = z;

        for (nm_size_t i=1; i<=num_terms; i++) {
            auto denominator = (2*i) - 1;
            sum += term / denominator;
            term *= z_squared;
        }

        T ln_m = 2 * sum;

        return (ln_m * inv_ln2_v<T>) + e;
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