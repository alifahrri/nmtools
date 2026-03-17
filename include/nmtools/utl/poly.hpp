#ifndef NMTOOLS_UTL_POLY_HPP
#define NMTOOLS_UTL_POLY_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/traits/is_resizable.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"
#include "nmtools/meta/bits/transform/get_element_type.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/transform/max_len.hpp"
#include "nmtools/utl/algorithm.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/vector.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/tuple.hpp"

#include "nmtools/utl/fmath.hpp"
#include "nmtools/utl/remez.hpp"
#include "nmtools/meta/utl/array.hpp"

// polynomial approximation
namespace nmtools::utl
{
    template <typename T>
    constexpr auto reduce_range(T x)
    {
        auto k = utl::round(x / (pi_v<T> / T(2)));
        auto r = x - (k * (pi_v<T> / T(2)));

        // TODO: infer type
        return utl::tuple{int32_t(k) % 4, r};
    }

    template <typename T, typename sin_coeffs_t, typename cos_coeffs_t>
    constexpr auto sin_poly(T x, const sin_coeffs_t& sin_coeffs, const cos_coeffs_t& cos_coeffs)
    {
        const auto [k,r] = reduce_range(x);

        auto t = r * r;
        if (k == 0) {
            auto result = r * horner_poly(t,sin_coeffs);
            return result;            
        } else if (k == 1) {
            auto result = horner_poly(t,cos_coeffs);
            return result;
        } else if (k == 2) {
            auto result = r * horner_poly(t,sin_coeffs);
            return -result;
        } else {
            // assume k == 3
            auto result = horner_poly(t,cos_coeffs);
            return -result;
        }
    } // sin_poly

    template <typename T, typename cos_coeffs_t, typename sin_coeffs_t>
    constexpr auto cos_poly(T x, const cos_coeffs_t& cos_coeffs, const sin_coeffs_t& sin_coeffs)
    {
        const auto [k,r] = reduce_range(x);

        auto t = r * r;

        if (k == 0) {
            auto result = horner_poly(t,cos_coeffs);
            return result;
        } else if (k == 1) {
            auto result = r * horner_poly(t,sin_coeffs);
            return -result;
        } else if (k == 2) {
            auto result = horner_poly(t,cos_coeffs);
            return -result;
        } else {
            // assume k == 3
            auto result = r * horner_poly(t,sin_coeffs);
            return result;
        }
    } // cos_poly

    template <typename T, typename coeffs_t>
    constexpr auto exp2_poly(T x, const coeffs_t& coeffs)
    {
        auto k = utl::round(x);
        auto r = x - k;
        auto poly_val = horner_poly(r,coeffs);
        return utl::ldexp(poly_val,(int)k);
    } // exp2_poly

    template <typename T, typename coeffs_t>
    constexpr auto log_poly(T x, const coeffs_t& coeffs)
    {
        // TODO: error on x < 0
        // TODO: return inf if x == inf

        const auto [m_,e_] = frexp(x);

        T m = m_ * 2;
        T e = e_ - 1;

        T z = (m - 1) / (m + 1);

        auto poly_val = horner_poly(z*z,coeffs);

        T ln_m = 2 * z * poly_val;

        return ln_m + (e * ln2_v<T>);
    }

    template <typename T, typename coeffs_t>
    constexpr auto log2_poly(T x, const coeffs_t& coeffs)
    {
        // TODO: error on x < 0
        // TODO: return inf if x == inf

        const auto [m_,e_] = frexp(x);

        T m = m_ * 2;
        T e = e_ - 1;

        T z = (m - 1) / (m + 1);

        auto poly_val = horner_poly(z*z,coeffs);

        T ln_m = 2 * z * poly_val;

        return (ln_m * inv_ln2_v<T>) + e;
    }

    #ifndef NMTOOLS_UTL_REMEZ_DEGREE
    #define NMTOOLS_UTL_REMEZ_DEGREE (ct_v<4>)
    #endif // NMTOOLS_UTL_REMEZ_DEGREE

    #ifndef NMTOOLS_UTL_REMEZ_ITER
    #define NMTOOLS_UTL_REMEZ_ITER (10)
    #endif // NMTOOLS_UTL_REMEZ_ITER

    constexpr auto obj_fun_cos = [](auto t){
        using T = decltype(t);
        return T(utl::taylor_cos(utl::sqrt(utl::abs(t))));
    };
    constexpr auto obj_fun_sin = [](auto t){
        using T = decltype(t);
        t = utl::abs(t);
        if (t < 1e-15) {
            return T(1.0);
        } else {
            return T(utl::taylor_sin(utl::sqrt(t)) / utl::sqrt(t));
        }
    };

    // objective functions for remez
    /********************************************************************* */

    struct cos_obj_fun_t
    {
        static constexpr auto domain()
        {
            constexpr auto a = double(0);
            constexpr auto q_pi = utl::pi_v<double> / 4;
            constexpr auto b = q_pi * q_pi;
            return utl::tuple{a,b};
        }

        template <typename T>
        constexpr auto operator()(T t) const
        {
            return T(utl::taylor_cos(utl::sqrt(utl::abs(t))));
        };
    };

    struct sin_obj_fun_t
    {
        static constexpr auto domain()
        {
            constexpr auto a = double(0);
            constexpr auto q_pi = utl::pi_v<double> / 4;
            constexpr auto b = q_pi * q_pi;
            return utl::tuple{a,b};
        }

        template <typename T>
        constexpr auto operator()(T t) const
        {
            t = utl::abs(t);
            if (t < 1e-15) {
                return T(1.0);
            } else {
                return T(utl::taylor_sin(utl::sqrt(t)) / utl::sqrt(t));
            }
        }
    };

    struct exp2_obj_fun_t
    {
        static constexpr auto domain()
        {
            constexpr double a = -0.5;
            constexpr double b = 0.5;
            return utl::tuple{a,b};
        }

        template <typename T>
        constexpr auto operator()(T t) const
        {
            return T(utl::exp2_maclaurin(t));
        }
    };

    struct log_obj_fun_t
    {
        static constexpr auto domain()
        {
            constexpr double a = 0;
            constexpr double b = double(1) / double(9);
            return utl::tuple{a,b};
        }

        template <typename T>
        constexpr auto operator()(T t) const
        {
            return T(utl::log_maclaurin(t));
        }
    };

    // remez coeffs
    /********************************************************************* */

    template <typename F, typename T, auto degree=5>
    struct remez_coeffs;

    #if nmtools_has_constexpr_bit_cast
    template <typename F, typename T, auto degree>
    struct remez_coeffs
    {
        static constexpr auto value = solve_remez(
            F{}
            , utl::get<0>(F::domain())
            , utl::get<1>(F::domain())
            , ct_v<degree>
        );

        constexpr auto size() const noexcept
        {
            return value.size();
        }

        constexpr auto operator[](nm_size_t i) const noexcept
        {
            return value[i];
        }
    };
    #else
    template <typename T>
    struct remez_coeffs<
        cos_obj_fun_t, T, 4
    > {
        static constexpr auto value = utl::array<T,6>{
            1.000000
            , -5.00000e-1
            , 4.16666e-2
            , -1.38888e-3
            , 2.47998045e-4
            , -2.72364189e-7
        };

        constexpr auto size() const noexcept
        {
            return value.size();
        }

        constexpr auto operator[](nm_size_t i) const noexcept
        {
            return value[i];
        }
    };

    template <typename T>
    struct remez_coeffs<
        sin_obj_fun_t, T, 4
    > {
        static constexpr auto value = utl::array<T,6>{
            1.000000
            , -1.66667e-1
            , 8.33333e-3
            , -1.98412647e-4
            , 2.75555594e-6
            , -2.47766355e-8
        };

        constexpr auto size() const noexcept
        {
            return value.size();
        }

        constexpr auto operator[](nm_size_t i) const noexcept
        {
            return value[i];
        }
    };

    template <typename T>
    struct remez_coeffs<
        exp2_obj_fun_t, T, 5
    > {
        static constexpr auto value = utl::array<T,7>{
            1.0
            , 0.6931471805599453
            , 0.2402265069591007
            , 0.05550410866482158
            , 0.009618129107628477
            , 0.0013333558146428443
            , 0.0001540353039338161
        };

        constexpr auto size() const noexcept
        {
            return value.size();
        }

        constexpr auto operator[](nm_size_t i) const noexcept
        {
            return value[i];
        }
    };

    template <typename T>
    struct remez_coeffs<
        log_obj_fun_t, T, 3
    > {
        static constexpr auto value = utl::array<T,5>{
            1.0
            , 0.3333333333333333
            , 0.2000000000000000
            , 0.1428571428571428
            , 0.1111111111111111
        };

        constexpr auto size() const noexcept
        {
            return value.size();
        }

        constexpr auto operator[](nm_size_t i) const noexcept
        {
            return value[i];
        }
    };
    #endif // nmtools_has_constexpr_bit_cast

    template <typename T, typename degree_t=ct<4>>
    constexpr auto cos(T x, degree_t=degree_t{})
    {
        #if 0
        constexpr auto a = double(0);
        constexpr auto q_pi = utl::pi_v<double> / 4;
        constexpr auto b = q_pi * q_pi;
        constexpr auto cos_coeffs = solve_remez(obj_fun_cos,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        constexpr auto sin_coeffs = solve_remez(obj_fun_sin,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        #elif 0
        constexpr auto cos_coeffs = utl::array<T,6>{1.000000, -5.00000e-1, 4.16666e-2, -1.38888e-3, 2.47998045e-4, -2.72364189e-7};
        constexpr auto sin_coeffs = utl::array<T,6>{1.000000, -1.66667e-1, 8.33333e-3, -1.98412647e-4, 2.75555594e-6, -2.47766355e-8};
        #else
        constexpr auto cos_coeffs = remez_coeffs<cos_obj_fun_t,T,degree_t::value>{};
        constexpr auto sin_coeffs = remez_coeffs<sin_obj_fun_t,T,degree_t::value>{};
        #endif

        return cos_poly(x,cos_coeffs,sin_coeffs);
    }

    template <typename T, typename degree_t=ct<4>>
    constexpr auto sin(T x, degree_t=degree_t{})
    {
        #if 0
        constexpr auto a = double(0);
        constexpr auto b = double(utl::pow(double(utl::pi_v<double> / 4), 2));
        constexpr auto cos_coeffs = solve_remez(obj_fun_cos,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        constexpr auto sin_coeffs = solve_remez(obj_fun_sin,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        #elif 0
        constexpr auto cos_coeffs = utl::array<T,6>{1.000000, -5.00000e-1, 4.16666e-2, -1.38888e-3, 2.47998045e-4, -2.72364189e-7};
        constexpr auto sin_coeffs = utl::array<T,6>{1.000000, -1.66667e-1, 8.33333e-3, -1.98412647e-4, 2.75555594e-6, -2.47766355e-8};
        #else
        constexpr auto cos_coeffs = remez_coeffs<cos_obj_fun_t,T,degree_t::value>{};
        constexpr auto sin_coeffs = remez_coeffs<sin_obj_fun_t,T,degree_t::value>{};
        #endif

        return sin_poly(x,sin_coeffs,cos_coeffs);
    }

    template <typename T, typename degree_t=ct<5>>
    constexpr auto exp(T x, degree_t=degree_t{})
    {
        #if 0
        constexpr double a = -0.5;
        constexpr double b = 0.5;
        constexpr auto obj_fun = [](auto t) {
            return utl::exp2_maclaurin(t);
        };
        constexpr auto coeffs = solve_remez(obj_fun,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        #elif 0
        constexpr auto coeffs = utl::array<T,7>{
            1.0f
            ,0.6931471805599453f
            ,0.2402265069591007f
            ,0.05550410866482158f
            ,0.009618129107628477f
            ,0.0013333558146428443f
            ,0.0001540353039338161f
        };
        #else
        constexpr auto coeffs = remez_coeffs<exp2_obj_fun_t,T,degree_t::value>{};
        #endif

        auto y = x * inv_ln2_v<T>;
        auto k = utl::round(y);
        auto r = y - k;

        auto poly = horner_poly(r,coeffs);

        return utl::ldexp(poly,int(k));
    }

    template <typename T, typename degree_t=ct<5>>
    constexpr auto exp2(T x, degree_t=degree_t{})
    {
        #if 0
        constexpr double a = -0.5;
        constexpr double b = 0.5;
        constexpr auto obj_fun = [](auto t) {
            return utl::exp2_maclaurin(t);
        };
        constexpr auto coeffs = solve_remez(obj_fun,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_ITER);
        #elif 0
        constexpr auto coeffs = utl::array<T,7>{
            1.0f
            ,0.6931471805599453f
            ,0.2402265069591007f
            ,0.05550410866482158f
            ,0.009618129107628477f
            ,0.0013333558146428443f
            ,0.0001540353039338161f
        };
        #else
        constexpr auto coeffs = remez_coeffs<exp2_obj_fun_t,T,degree_t::value>{};
        #endif

        return exp2_poly(x,coeffs);
    }

    template <typename T, typename degree_t=ct<7>>
    constexpr auto log(T x, degree_t=degree_t{})
    {
        #if 0
        constexpr double a = 0;
        constexpr double b = double(1) / double(9);
        constexpr auto obj_fun = [](auto t){
            return utl::log_maclaurin(t);
        };
        constexpr auto coeffs = solve_remez(obj_fun,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_DEGREE);
        #elif 0
        constexpr auto coeffs = utl::array<T,5>{
            1.0f,
            0.3333333333333333f,
            0.2000000000000000f,
            0.1428571428571428f,
            0.1111111111111111f
        };
        #else
        constexpr auto coeffs = remez_coeffs<log_obj_fun_t,T,degree_t::value>{};
        #endif

        return log_poly(x,coeffs);
    }

    template <typename T, typename degree_t=ct<7>>
    constexpr auto log10(T x, degree_t=degree_t{})
    {
        auto t = utl::log(x,degree_t{});
        return t * inv_ln10_v<T>;
    }

    template <typename T, typename degree_t=ct<7>>
    constexpr auto log2(T x, degree_t=degree_t{})
    {
        #if 0
        constexpr double a = 0;
        constexpr double b = double(1) / double(9);
        constexpr auto obj_fun = [](auto t){
            return utl::log_maclaurin(t);
        };
        constexpr auto coeffs = solve_remez(obj_fun,a,b,NMTOOLS_UTL_REMEZ_DEGREE,NMTOOLS_UTL_REMEZ_DEGREE);
        #elif 0
        constexpr auto coeffs = utl::array<T,5>{
            1.0f,
            0.3333333333333333f,
            0.2000000000000000f,
            0.1428571428571428f,
            0.1111111111111111f
        };
        #else
        constexpr auto coeffs = remez_coeffs<log_obj_fun_t,T,degree_t::value>{};
        #endif

        return log2_poly(x,coeffs);
    }
}

#endif // NMTOOLS_UTL_POLY_HPP