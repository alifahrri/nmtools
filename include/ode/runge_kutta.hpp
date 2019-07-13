#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP

#include "utility.hpp"
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

            template <typename F, typename T, typename Y, typename H, typename A, typename C, typename Ks>
            constexpr auto k(size_t n, const F &f, const T &x, const Y &y, const H& h, const A &a, const C& c, const Ks &ks) 
                -> decltype(a[0][0],c[0],f(x,y),std::decay_t<decltype(ks[0])>())
            {
                if (n) {
                    auto i = n-1;
                    using k_type = std::decay_t<decltype(ks[0])>;
                    k_type sum{0};
                    for (size_t j=0; j<n; j++)
                        sum += a[i][j] * ks[j];
                    return f(x+c[i]*h,y+h*sum);
                } else {
                    return f(x,y);
                }
            }

#if 0
            template <typename F, typename T, typename A, typename B, typename C>
            constexpr auto rk_driver(F &f, T x, T yi, T h, const A& a, const B& b, const C &c) {
                using y_t = std::decay_t<decltype(yi)>;
                using Ks = std::decay_t<decltype(b[0])>;
                y_t sum{}; Ks ks;
            }

            template <typename F, typename T, typename A, typename B, typename C>
            constexpr auto rk_driver(F &f, T xi, T xf, T yi, T h, const A& a, const B& b, const C &c) {
                auto n = (xf-xi) / h;
                for (size_t i=0; i<n; i++) {
                    
                }
            }
#endif
        } // namespace detail

        template <typename F>
        constexpr auto ralston(F &f) {

        }
    } // namespace ode
} // namespace numeric
#endif //RUNGE_KUTTA_HPP