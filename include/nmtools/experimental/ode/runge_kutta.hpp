#ifndef NMTOOLS_RUNGE_KUTTA_HPP
#define NMTOOLS_RUNGE_KUTTA_HPP

#include "nmtools/utility.hpp"
#include <cassert>
#include <array>
#include <iterator>
#include <type_traits>

namespace nmtools::ode {
    namespace detail {

        // template <typename T>
        // constexpr size_t size(T t) {
        //     return t.N;
        // }
        // template <typename T>
        // constexpr auto value(T t,size_t i) -> decltype(t.values[i]) {
        //     return t.values[i];
        // }

        // template <size_t N, typename Scalar, typename P>
        // constexpr Scalar x_term(size_t i, P p, Scalar h) {
        //     return value(p,i)*h;
        // }
        // template <size_t N, typename Scalar, typename Q, typename K>
        // constexpr Scalar y_term(size_t i, K k, Q q, Scalar h) {
        //     // return i==1 ? value(q,i-1)*value(k,)
        // }
        // template <size_t N, typename F, typename Scalar, typename P, typename Q>
        // struct K {
        //     constexpr K(const F &f, Scalar x, Scalar y, Scalar h, P p, Q q) {
        //         static_assert(size(p)==(N-1));
        //         static_assert(size(q)==helper::detail::triangular_number(N-1));
        //     }
        //     // const Scalar k[N];
        // };

        template <typename A, typename B, typename C>
        constexpr auto butcher_tableau(A &a, B &b, C &c) 
            -> decltype(a[0][0], b[0], c[0], bool())
        {
            assert( std::size(a) == std::size(c) );
            assert( std::size(b) == std::size(c)+1 );
            auto s = std::size(c);
            for (size_t i=0; i<s; i++) {
                using value_t = std::decay_t<decltype(c[0])>;
                value_t a_sum{};
                for (size_t j=0; j<=i; j++)
                    a_sum += a[i][j];
                if (a_sum != c[i])
                    return false;
            }
            return true;
        }

        /**
         * @brief compute coefficients for explicit Runge-Kutta methods
         * \f[
         *      k_s = f(t_n + c_s h, y_n + h(a_{s1}k_1 + a_{s2}k_2 + ... + a_{s,s-1}k_{s-1}))
         * \f]
         * 
         * @tparam F
         * @tparam T real number
         * @tparam Y real number
         * @tparam H real number
         * @tparam A matrix-like
         * @tparam C vector-like
         * @tparam Ks container
         * @param n number of stages
         * @param f differential equations
         * @param x independent variable
         * @param y dependent variable
         * @param h step
         * @param a Runge-Kutta Matrix
         * @param c nodes
         * @param ks 
         * @return constexpr auto 
         */
        template <typename F, typename T, typename Y, typename H, typename A, typename C, typename Ks>
        constexpr auto compute_k(size_t n, const F &f, const T &x, const Y &y, const H& h, const A &a, const C& c, const Ks &ks)
            -> decltype(a[0][0],ks[0],f(x,y),T())
        {
            using k_type = std::decay_t<decltype(ks[0])>;
            using Scalar = T;
            if (n) {
                k_type sum{0};
                auto i = n-1;
                for (size_t j=0; j<n; j++) {
                    sum += a[i][j] * ks[j];
                }
                auto kn = f(x+c[i]*h,y+h*sum);
                return kn;
            } else {
                auto kn = f(x,y);
                return kn;
            }
        }

        /**
         * @brief evaluate ODE for single-step
         * 
         * @tparam F 
         * @tparam X real number
         * @tparam T real number
         * @tparam A matrix-like
         * @tparam B vector-like
         * @tparam C vector-like
         * @tparam void 
         * @param f differential equation
         * @param x independent variable
         * @param yi initial 'dependent variable'
         * @param h independent variable step
         * @param a Runge-Kutta Matrix
         * @param b weights
         * @param c nodes
         * @param logger 
         * @return decltype(f(x,yi),b[0],T()) 
         */
        template <typename F, typename X, typename T, typename A, typename B, typename C>
        constexpr auto rk_driver(F &f, X x, T yi, X h, const A& a, const B& b, const C &c) 
            -> decltype(f(x,yi),b[0],T())
        {
            namespace hp = helper;
            /* TODO : fix logger template param */
            using Scalar = T;
            using Ks = std::decay_t<decltype(b)>;
            T sum{}; Ks ks{};
            /* number of 'stages' */
            auto s = std::size(b);
            if constexpr (meta::is_resizeable_v<Ks>)
                ks.resize(s);
            for (size_t i=0; i<s; i++) {
                /* compute runge kutta coefficients for this stages */
                auto ki = compute_k(i,f,x,yi,h,a,c,ks);
                ks[i] = ki;
                sum += b[i]*ki;
            }
            return yi + h*sum;
        }

        /**
         * @brief helper type
         * 
         * @tparam Args 
         */
        template<typename ...Args>
        struct scalar_return_t {};
    } // namespace detail

    /**
     * @brief evaluate ODE initial problem 
     * using generic driver for Runge-Kutta family
     * \f[
     *      y_{n+1} = y_{n} + h \sum_{i=1}^{s}{b_i k_i}
     * \f]
     * 
     * @tparam F 
     * @tparam T real number
     * @tparam A matrix-like
     * @tparam B vector-like
     * @tparam C vector-like
     * @tparam void 
     * @param f differential equations
     * @param xi initial independent variable
     * @param xf final independent variable
     * @param yi initial dependent variable
     * @param h independent variable step
     * @param a Runge-Kutta Matrix
     * @param b weights
     * @param c nodes
     * @param logger optional intermediate value logger
     * no runtime cost (logging block won't be compiled) if left unspecified
     * @return constexpr auto 
     * @cite rk_driver_wikipedia
     */
    template <typename F, typename T, typename A, typename B, typename C, typename Logger = std::nullptr_t>
    constexpr auto rk_driver(F &f, T xi, T xf, T yi, T h, const A& a, const B& b, const C &c, Logger *logger = Logger{}) {
        /* TODO : fix logger template param */
        using Scalar = T;
        auto n = (xf-xi) / h;
        T yn = yi;
        for (size_t i=0; i<size_t(n); i++) {
            auto x = xi + i*h;
            yn = detail::rk_driver(f,x,yn,h,a,b,c);
            /* TODO : fix logger template param */
            if constexpr (!std::is_same_v<Logger,std::nullptr_t>) {
                static_assert(std::is_pointer_v<decltype(logger)>);
                (*logger)(std::map<std::string,T>{{"i",i},{"x",x},{"yn",yn}});
            }
        }
        return yn;
    }

    /* template alias for syntax sugar */
    template <typename dtype, size_t n>
    using array = std::array<dtype,n>;

    /**
     * @brief evaluate ODE initial value problem
     * using 2nd-order ralston Runge-Kutta method
     * 
     * @tparam F 
     * @tparam T real number
     * @tparam Y real number
     * @tparam Logger=std::nullptr_t 
     * @param f callable differential equation
     * \f[
     *      \frac{dy}{dx} = f(x,y)
     * \f]
     * @param xi initial independent variable
     * @param xf final independent variable
     * @param yi initial dependent variable
     * @param h independent variable step
     * @param logger optional intermediate value logger
     * no runtime cost (logging block won't be compiled) if left unspecified
     * @return constexpr auto 
     * @cite rk_ralston_wikipedia
     */
    template <typename F, typename T, typename Y, typename Logger=std::nullptr_t>
    constexpr auto rk_ralston(F &f, T xi, T xf, Y yi, T h, Logger *logger = Logger{}) {
        constexpr array<double,1> c = { 2./3. };
        constexpr array<array<double,1>,1> a = { 2./3. };
        constexpr array<double,2> b = {
            1./4., 3./4.
        };
        return rk_driver(f,xi,xf,yi,h,a,b,c,logger);
    }

    /**
     * @brief evaluate ODE initial value problem 
     * using 2nd-order midpoint Runge-Kutta method
     * 
     * @tparam F 
     * @tparam T real number
     * @tparam Y real number
     * @tparam Logger=std::nullptr_t 
     * @param f callable differential equation
     * \f[
     *      \frac{dy}{dx} = f(x,y)
     * \f]
     * @param xi initial independent variable
     * @param xf final independent variable
     * @param yi initial dependent variable
     * @param h independent variable step
     * @param logger optional intermediate value logger
     * no runtime cost (logging block won't be compiled) if left unspecified
     * @return constexpr auto 
     * @cite rk_midpoint_wikipedia
     */
    template <typename F, typename T, typename Y, typename Logger=std::nullptr_t>
    constexpr auto rk_midpoint(F &f, T xi, T xf, Y yi, T h, Logger *logger = Logger{}) {
        constexpr array<double,1> c = { 1./2. };
        constexpr array<array<double,1>,1> a = { 1./2. };
        constexpr array<double,2> b = {
            0., 1.
        };
        return rk_driver(f,xi,xf,yi,h,a,b,c,logger);
    }

    /**
     * @brief evaluate ODE initial value problem using the Runge-Kutta method
     * 
     * @tparam F callable differential equation
     * @tparam T real number
     * @tparam Y real number
     * @tparam Logger=std::nullptr_t 
     * @param f callable differential equation
     * \f[
     *      \frac{dy}{dx} = f(x,y)
     * \f]
     * @param xi initial independent variable
     * @param xf final independent variable
     * @param yi initial dependent variable
     * @param h independent variable step
     * @param logger optional intermediate value logger
     * no runtime cost (logging block won't be compiled) if left unspecified
     * @return constexpr auto 
     * @cite rk_wikipedia
     */
    template <typename F, typename T, typename Y, typename Logger=std::nullptr_t>
    constexpr auto rk4(F &f, T xi, T xf, Y yi, T h, Logger *logger = Logger{}) {
        constexpr array<double,3>  c = { 1./2., 1./2., 1. };
        /* TODO : support std::ratio and skip multiply with zero (?) */
        constexpr array<array<double,3>,3> a = {{
            { 1./2., 0.,    0. },
            { 0.,    1./2., 0. },
            { 0.,    0.,    1. }
        }};
        constexpr std::array<double,4> b = {
            1./6., 1./3., 1./3., 1./6.
        };
        return rk_driver(f,xi,xf,yi,h,a,b,c,logger);
    }
} // namespace nmtools::ode
#endif //NMTOOLS_RUNGE_KUTTA_HPP