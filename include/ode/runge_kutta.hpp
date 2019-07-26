#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP

#include "utility.hpp"
#include <array>
#include <iterator>
#include <type_traits>

namespace numeric {
    namespace ode {
        namespace detail {
            // template <size_t N, typename Scalar, int ratio, int ... p_constants>
            // struct P {
            //     static_assert(sizeof...(p_constants)==(N-1));
            //     constexpr static Scalar[N-1] p = {
            //         (Scalar(p_constants)/ratio))...
            //     };
            // };
            // template <size_t N, typename Scalar>
            // struct Q {

            // };

            // using declval = std::declval;

            template <typename T>
            constexpr size_t size(T t) {
                return t.N;
            }
            template <typename T>
            constexpr auto value(T t,size_t i) -> decltype(t.values[i]) {
                return t.values[i];
            }

            template <size_t N, typename Scalar, typename P>
            constexpr Scalar x_term(size_t i, P p, Scalar h) {
                return value(p,i)*h;
            }
            template <size_t N, typename Scalar, typename Q, typename K>
            constexpr Scalar y_term(size_t i, K k, Q q, Scalar h) {
                // return i==1 ? value(q,i-1)*value(k,)
            }
            template <size_t N, typename F, typename Scalar, typename P, typename Q>
            struct K {
                constexpr K(const F &f, Scalar x, Scalar y, Scalar h, P p, Q q) {
                    static_assert(size(p)==(N-1));
                    static_assert(size(q)==helper::detail::triangular_number(N-1));
                }
                // const Scalar k[N];
            };

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

            template <typename F, typename T, typename Y, typename H, typename A, typename C, typename Ks, typename Logger = void>
            constexpr auto k(size_t n, const F &f, const T &x, const Y &y, const H& h, const A &a, const C& c, const Ks &ks, Logger *logger = nullptr) 
                -> std::enable_if_t< std::conjunction_v < 
                    traits::is_2d_array< A >, 
                    std::is_same< std::void_t <
                        decltype(std::declval<C>()[0]),
                        decltype(std::declval<F>()(std::declval<T>(),std::declval<Y>()))>, void 
                    > /* is_same */
                >, /* conjuction */ std::decay_t< decltype(ks[0]) > > /* enable_if */
            {
                using k_type = std::decay_t<decltype(ks[0])>;
                /* TODO : fix logger template param */
                using Scalar = T;
                if (n) {
                    k_type sum{0};
                    auto i = n-1;
                    for (size_t j=0; j<n; j++) {
                        sum += a[i][j] * ks[j];
                        LOGVAR(logger, n, i, j, a[i][j], ks[j]);
                    }
                    auto kn = f(x+c[i]*h,y+h*sum);
                    LOGVAR(logger, n, kn);
                    return kn;
                } else {
                    auto kn = f(x,y);
                    LOGVAR(logger, n, kn, x, y);
                    return kn;
                }
            }

            template <typename F, typename T, typename Y, typename H, typename A, typename C, typename Ks, typename Logger = void>
            constexpr auto k(size_t n, const F &f, const T &x, const Y &y, const H& h, const A &a, const C& c, const Ks &ks, Logger *logger = nullptr) 
                -> std::enable_if_t< std::conjunction_v < 
                    std::negation< traits::is_2d_array< A > >,  /* not 2d array */
                    std::is_same< std::void_t <
                        decltype(std::declval<C>()[0]),         /* requires c[0] */
                        decltype(std::declval<F>()(std::declval<T>(),std::declval<Y>()))>, void 
                    > /* is_same */
                >, /* conjuction */ std::decay_t< decltype(ks[0]) > > /* enable_if */
            {
                namespace hpd = helper::detail;
                /* TODO : fix logger template param */
                using Scalar = T;
                using k_type = std::decay_t<decltype(ks[0])>;
                if (n) {
                    k_type sum{0};
                    auto i = n-1;
                    auto a_idx_offset{0};
                    for (size_t l=1; l<n; l++)
                        a_idx_offset += l;
                    for (size_t j=0; j<n; j++) {
                        auto a_idx = a_idx_offset + j;
                        sum += a[a_idx] * ks[j];
                        LOGVAR(logger, n, i, j, a_idx_offset, a[a_idx], ks[j]);
                    }
                    auto kn = f(x+c[i]*h,y+h*sum);
                    LOGVAR(logger, n, kn);
                    return kn;
                } else {
                    auto kn = f(x,y);
                    LOGVAR(logger, n, kn, x, y);
                    return kn;
                }
            }

            template <typename F, typename X, typename T, typename A, typename B, typename C, typename Logger = void>
            constexpr auto rk_driver(F &f, X x, T yi, X h, const A& a, const B& b, const C &c, Logger *logger = nullptr) 
                -> decltype(f(x,yi),b[0],T())
            {
                namespace hp = helper;
                /* TODO : fix logger template param */
                using Scalar = T;
                using Ks = std::decay_t<decltype(b)>;
                T sum{}; Ks ks{};
                for (size_t i=0; i<std::size(b); i++) {
                    auto ki = k(i,f,x,yi,h,a,c,ks,logger);
                    auto p = std::begin(ks)+i;
                    sum += b[i]*ki;
                    /* TODO : support constexpr 'insert' */
                    hp::insert(ks,p,ki);
                    /* TODO : fix logger template param */
                    LOGVAR(logger, i, b[i], ki);
                }
                return yi + h*sum;
            }

            template <typename F, typename T, typename A, typename B, typename C, typename Logger = void>
            constexpr auto rk_driver(F &f, T xi, T xf, T yi, T h, const A& a, const B& b, const C &c, Logger *logger = nullptr) {
                /* TODO : fix logger template param */
                using Scalar = T;
                auto n = (xf-xi) / h;
                T yn = yi;
                for (size_t i=0; i<size_t(n); i++) {
                    auto x = xi + i*h;
                    yn = rk_driver(f,x,yn,h,a,b,c,logger);
                    /* TODO : fix logger template param */
                    LOGVAR(logger, i, x, yn);
                }
                return yn;
            }
        } // namespace detail

        template <typename F, typename T, typename Y>
        constexpr auto ralston(F &f, T xi, T xf, Y yi, T h) {
            constexpr std::array<double,1> c = { 2./3. };
            constexpr std::array<double,1> a = { 2./3. };
            constexpr std::array<double,2> b = {
                1./4., 3./4.
            };
            return detail::rk_driver(f,xi,xf,yi,h,a,b,c);
        }

        template <typename F, typename T, typename Y>
        constexpr auto midpoint(F &f, T xi, T xf, Y yi, T h) {
            constexpr std::array<double,1> c = { 1./2. };
            constexpr std::array<double,1> a = { 1./2. };
            constexpr std::array<double,2> b = {
                0., 1.
            };
            return detail::rk_driver(f,xi,xf,yi,h,a,b,c);
        }

        template <typename F, typename T, typename Y, typename Logger = void>
        constexpr auto rk4(F &f, T xi, T xf, Y yi, T h, Logger *logger = nullptr) {
            constexpr std::array<double,3>  c = { 1./2., 1./2., 1. };
            /* TODO : support std::ratio and skip multiply with zero (?) */
            constexpr std::array<std::array<double,3>,3> a = {{
                { 1./2., 0.,    0. },
                { 0.,    1./2., 0. },
                { 0.,    0.,    1. }
            }};
            constexpr std::array<double,4> b = {
                1./6., 1./3., 1./3., 1./6.
            };
            return detail::rk_driver(f,xi,xf,yi,h,a,b,c,logger);
        }
    } // namespace ode
} // namespace numeric
#endif //RUNGE_KUTTA_HPP