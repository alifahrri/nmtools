#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP

#include "utility.hpp"

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

            // template <size_t order, typename ...Scalar>
            // struct RK_K : RK_K<order-1> {
            //     constexpr RK_K(Scalar ...) : k() {};
            //     Scalar k;
            // };

            // template <>
            // struct RK_K<1> {
            //     constexpr RK_K() {};
                
            // };
        } // namespace detail
    } // namespace ode
} // namespace numeric
#endif //RUNGE_KUTTA_HPP