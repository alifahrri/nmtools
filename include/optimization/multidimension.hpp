#ifndef MULTIDIMENSION_HPP
#define MULTIDIMENSION_HPP

#include <cmath>

namespace numeric {
    namespace optimization {
        /* sfinae stuff */
        namespace detail {
            constexpr auto transpose(auto vec) -> decltype(vec.transpose())
            {
                return vec.transpose();
            }
            constexpr auto transpose(auto vec) -> decltype(vec.t())
            {
                return vec.t();
            }
        } // namespace detail

        template <typename F, typename G, typename Vector, typename Scalar>
        auto inexact_line_search(F &f, G &g, Vector x0, Vector d0, Scalar rho, Scalar sigma, Scalar tau, Scalar chi)
        {
            using transpose = detail::transpose;
            Scalar alpha_l{0}, alpha_u{1e99};
            auto fl = f(x0+alpha_l*d0);
            auto dfl = transpose(g(x0+alpha_l*d0))*d0;
        }

        template <typename F, typename G, typename Vector, typename Scalar>
        auto steepest_descent(F &f, G &g, Vector x1, Scalar eps, size_t &k, Scalar alpha)
        {
            /* step 1*/
            k = 1; alpha = Scalar(1);
            auto xk = x1;
            auto f1 = f(x1);
            do {
                /* step 2 */
                auto gk = g(xk);
                auto dk = -gk; auto a_hat = alpha;
                auto f_hat = f(xk-a_hat*gk);
                
            }
        }
    } // namespace optimization
} // namespace numeric
#endif // MULTIDIMENSION_HPP