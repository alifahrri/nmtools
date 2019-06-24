#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP

#include "utility.hpp"

namespace numeric {
    namespace ode {
        namespace detail {

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