#ifndef NMTOOLS_UNCONSTRAINED_OPTIMIZATION_HPP
#define NMTOOLS_UNCONSTRAINED_OPTIMIZATION_HPP

#include "nmtools/blas/blas.hpp"
#include "nmtools/utility.hpp"

#include <cstdio>
#include <cmath>
#include <tuple>
#include <array>
#include <algorithm>
#include <functional>

namespace nmtools {
    namespace optimization {
        namespace detail {

            template <typename X>
            constexpr auto transpose(X &&x) {
                static_assert(
                    std::is_arithmetic_v<X>,
                    "unsupported transpose operation"
                );
                return x;
            }
            
            /* boiler-plates */
            template<int...> struct seq {};

            template<int N,int...S>
            struct gens : gens<N-1, N-1, S...> {};

            template<int...S>
            struct gens<0,S...> {
                typedef seq<S...> type;
            };

            template<typename Op, typename...Args>
            struct OpInvoker {
                std::tuple<Args...> &params; /* xs */
                std::tuple<Args...> &values; /* fxs */
                Op *op;

                template<int...S>
                auto impl(seq<S...>) 
                {
                    return (*op)(std::get<S>(params)...,std::get<S>(values)...);
                }

                auto operator()()
                {
                    return impl(typename gens<sizeof...(Args)>::type{});
                }
            };
            /* boiler-plates end*/
            
            /* TODO : find more efficient way */
            template <typename F, typename Scalar, typename OptSelector, typename Updater, typename ErrorUpdater, typename...Args>
            auto generic(
                F &f, Args&...xs, Scalar &xopt, 
                OptSelector &selector, Updater &updater, ErrorUpdater &error_updater,
                size_t imax, size_t &iter, Scalar es, Scalar &ea, Scalar &fx) 
            {
                constexpr auto nx = sizeof...(xs);
                std::tuple<Args...> x{xs...};
                std::tuple<Args...> fxs{f(xs)...};
                auto selection = OpInvoker<OptSelector,Args...>{x, fxs, &selector};
                auto update = OpInvoker<Updater,Args...>{x, fxs, &updater};
                std::tie(xopt,fx) = selection();
                iter = 1;
                do {
                    std::tie(x,fxs) = update();
                    iter = iter+1;
                    std::tie(xopt,fx) = selection();
                    if(std::fabs(xopt) > 0)
                        ea = error_updater(xopt);
                } while(ea > es && iter < imax);
            }

            template <typename F, typename Scalar, typename Op = typename std::greater<Scalar>>
            auto gold_section(F &f, Scalar xlow, Scalar xhigh, Scalar &xopt, size_t imax, size_t &iter, Scalar es, Scalar &ea, Scalar &fx, const Op &op = Op{}) 
            {
                constexpr Scalar R = (std::sqrt(Scalar(5))-1)/2;
                auto xl = xlow; auto xh = xhigh;
                auto d = R * (xh - xl);
                Scalar x1 = xl + d; Scalar x2 = xh - d;
                Scalar xint;
                auto selector = [&](Scalar x1, Scalar x2, Scalar f1, Scalar f2) {
                    return (op(f1,f2) ? std::make_tuple(x1,f1) : std::make_tuple(x2,f2));
                };
                auto updater = [&](
                    Scalar &x1, Scalar &x2, Scalar &f1, Scalar &f2)
                {
                    d = R * d; xint = xh - xl;
                    if(op(f1,f2)) {
                        xl = x2; x2 = x1;
                        x1 = xl + d;
                        f2 = f1; f1 = f(x1);
                    } else {
                        xh = x1; x1 = x2;
                        x2 = xh - d;
                        f1 = f2; f2 = f(x2);
                    }
                    return std::make_tuple(std::make_tuple(x1,x2),std::make_tuple(f1,f2));
                };
                auto error_updater = [&](Scalar xopt) {
                    return (Scalar(1)-R) * std::fabs(xint/xopt) * 100;
                };
                using selector_t = decltype(selector);
                using updater_t = decltype(updater);
                using error_t = decltype(error_updater);
                detail::generic<F,Scalar,selector_t,updater_t,error_t,Scalar,Scalar>(
                    f,x1,x2,xopt,
                    selector,updater,error_updater,
                    imax,iter,es,ea,fx
                );
            }
        }
        
        template <typename F, typename Scalar, typename Op = typename std::greater<Scalar>>
        auto gold_section(F &f, Scalar xlow, Scalar xhigh, Scalar &xopt, size_t imax, size_t &iter, Scalar es, Scalar &ea, Scalar &fx, const Op &op = Op{}) {
            constexpr Scalar R = (std::sqrt(Scalar(5))-1)/2;
            auto xl = xlow; auto xh = xhigh;
            iter = 1;
            auto d = R * (xh - xl);
            auto x1 = xl + d; auto x2 = xh - d;
            auto f1 = f(x1); auto f2 = f(x2);
            if(op(f1,f2)) {
                xopt = x1;
                fx = f1;
            } else {
                xopt = x2;
                fx = f2;
            }
            do {
                d = R * d; auto xint = xh - xl;
                if(op(f1,f2)) {
                    xl = x2; x2 = x1;
                    x1 = xl + d;
                    f2 = f1; f1 = f(x1);
                } else {
                    xh = x1; x1 = x2;
                    x2 = xh - d;
                    f1 = f2; f2 = f(x2);
                }
                iter = iter + 1;
                if(op(f1,f2)) {
                    xopt = x1;
                    fx = f1;
                } else {
                    xopt = x2;
                    fx = f2;
                }
                if(std::fabs(xopt) > 0) {
                    ea = (Scalar(1)-R) * std::fabs(xint/xopt) * 100;
                }
            } while(ea > es && iter < imax);
        }
        
        template <typename F, typename Scalar, typename Op = typename std::greater<Scalar>, typename Logger = void>
        auto parabolic_interpolation(F &f, Scalar x0, Scalar x1, Scalar x2, Scalar &xopt, size_t imax, size_t &iter, Scalar es, Scalar &ea, Scalar &fx, const Op &op = Op{}, Logger *logger = nullptr)
        {
            auto f0 = f(x0); auto f1 = f(x1); auto f2 = f(x2);
            auto x3 = (f0*(x1*x1 - x2*x2) + f1*(x2*x2 - x0*x0) + f2*(x0*x0 - x1*x1)) /
                      (2*f0*(x1 - x2) + 2*f1*(x2 - x0) + 2*f2*(x0 - x1));
            auto f3 = f(x3);
            iter = 1;
            auto fx_old = fx;
            auto xopt_old = xopt;
            std::array<std::pair<Scalar,Scalar>,4> pts{
                std::make_pair(x0,f0), std::make_pair(x1,f1), 
                std::make_pair(x1,f2), std::make_pair(x3,f3), 
            };
            using pair_t = decltype(pts[0]);

            /* TODO : optimize */
            std::sort(pts.begin(), pts.end(),[&](pair_t lhs, pair_t rhs){
                return !op(lhs.first,rhs.first);
            });

            LOGVAR(logger, iter, x0, x1, x2, x3, f0, f1, f2, f3, ea, xopt, fx);
            do {
                xopt_old = xopt;
                fx_old = fx;

                auto opt_pair = std::minmax_element(pts.begin(), pts.end(), [&](pair_t a, pair_t b){
                    return a.second < b.second;
                });
                auto opt = (op(opt_pair.first->second,opt_pair.second->second) ?
                    opt_pair.first : opt_pair.second);
                std::tie(xopt,fx) = (*opt);

                /* assign ea for termination check */
                if(std::fabs((xopt - xopt_old)) > 0) 
                    ea = Scalar(100) * std::fabs((fx - fx_old) * (xopt - xopt_old));
                iter = iter + 1;

                if(opt == pts.begin())  {
                    opt++;
                } else if(opt == pts.end()) {
                    opt--;
                }
                x0 = (opt-1)->first;
                x1 = (opt)->first;
                x2 = (opt+1)->first;

                f0 = f(x0); f1 = f(x1); f2 = f(x2);
                x3 = (f0*(x1*x1 - x2*x2) + f1*(x2*x2 - x0*x0) + f2*(x0*x0 - x1*x1)) /
                      (2*f0*(x1 - x2) + 2*f1*(x2 - x0) + 2*f2*(x0 - x1));
                f3 = f(x3);

                LOGVAR(logger, iter, x0, x1, x2, x3, f0, f1, f2, f3, ea, xopt, fx);

                pts = {
                    std::make_pair(x0,f0), std::make_pair(x1,f1), 
                    std::make_pair(x2,f2), std::make_pair(x3,f3), 
                };
                /* TODO : optimize */
                std::sort(pts.begin(), pts.end(),[&](pair_t lhs, pair_t rhs){
                    return !op(lhs.first,rhs.first);
                });
            } while(ea > es && iter < imax);
            if(op(f3,fx)) {
                xopt = x3; fx = f3;
            }
            LOGVAR(logger, iter, x0, x1, x2, x3, f0, f1, f2, f3, ea, xopt, fx);
        }

        template <typename F, typename DF, typename DDF, typename Scalar, typename Op = std::greater<Scalar>, typename Logger = void>
        auto newton(F &f, DF &df, DDF &ddf, Scalar x0, Scalar &xopt, size_t imax, size_t &iter, Scalar es, Scalar &ea, Scalar &fx, const Op &op, Logger *logger = nullptr)
        {
            iter = 1;
            do {
                auto f0 = f(x0);
                auto df0 = df(x0);
                auto ddf0 = ddf(x0);
                auto x1 = x0 - (!op(ddf0,0) ? 1 : -1) * df0 / ddf0;
                auto f1 = f(x1);
                if(std::fabs(x1 - xopt) > 0) 
                    ea = Scalar(100) * std::fabs((f1-fx)/(x1-xopt));
                x0 = x1;
                xopt = x1;
                fx = f1;
                LOGVAR(logger, iter, x0, f0, df0, ddf0, x1, f1, xopt, fx, ea);
                iter = iter+1;
            } while(ea > es && iter < imax);
        } // newton

        /**
         * @brief backtracking line search with Armijo condition (Algorithm 3.1. in Nocedal's book)
         *  f(x_k + p_k \alpha) \leq f(x_k) + c_1 \alpha \nabla f_k^{T} p_k
         * 
         * @tparam F callable
         * @tparam DF callable
         * @tparam X vector-like or arithmetic
         * @tparam D vector-like or arithmetic
         * @tparam alpha_t scalar
         * @tparam rho_t scalar
         * @tparam c_t scalar
         * @param f objective function
         * @param g jacobian function
         * @param x_k initial state
         * @param p_k search direction
         * @param alpha initial step length \alpha
         * @param rho contraction factor \rho
         * @param c constant for armijo condition
         * @param max_iter 
         * @return constexpr auto alpha
         * @cite nocedal2006numerical_backtracikng_line_search
         */
        template <typename F, typename DF, typename X, typename D, typename alpha_t, typename rho_t, typename c_t>
        constexpr auto backtracking_line_search(F &&f, DF &&g, X &&x_k, D &&p_k, alpha_t alpha, rho_t rho, c_t c, size_t max_iter=10)
        {
            using blas::dot;
            using blas::mul;
            using blas::add;
            using direction_t = decltype(mul(p_k,alpha));
            /* make sure alpha_t, beta_t, tau_t have common type */
            using common_t = std::common_type_t<alpha_t,rho_t,c_t>;
            static_assert(
                traits::is_callable_v<F,X>              // F(X)
                && traits::is_callable_v<DF,X>          // DF(X)
                && (traits::is_array1d_v<X> || std::is_arithmetic_v<X>)
                && (traits::is_array1d_v<D> || std::is_arithmetic_v<D>)
                /* TODO: check if add(...), mul(...) (see ops below) are well-formed */
                , "unsupported type(s) for backtracking_armijo_line_search"
            );
            /* TODO : give warning or error if tau & beta > 0 */
            auto fk = f(x_k);
            auto gk = g(x_k);
            auto a  = alpha;
            auto dk = dot(gk,p_k);
            /* Armijo condition:
                f(x_k + p_k \alpha) \leq f(x_k) + c_1 \alpha_k \nabla f_k^{T} p_k
             */
            /* note: \nabla f_k^{T} p_k is performed using dot product */
            for (size_t i=0; i<max_iter; i++) {
                if ( f(add(x_k,mul(p_k,a))) > add(fk,mul(dk,a*c)) )
                    break;
                a = mul(a,rho);
            }
            return a;
        } // backtracking_armijo_line_search

        namespace detail {
            template <typename X, typename Scalar>
            auto line_search_interpolation(X &&f_0, X &&f_l, X &&df_l, Scalar &alpha_0, Scalar &alpha_u, Scalar alpha_l, Scalar tau)
            {
                if (alpha_0 < alpha_u)
                    alpha_u = alpha_0;
                auto alpha_hat = alpha_l + (
                    std::pow(alpha_0 - alpha_l, 2) * df_l /
                    ( 2 * (f_l - f_0 + (alpha_0 - alpha_l) * df_l) )
                );
                if (alpha_hat < alpha_l + tau * (alpha_u - alpha_l))
                    alpha_hat = alpha_l + tau * (alpha_u - alpha_l);
                if (alpha_hat > alpha_u - tau * (alpha_u - alpha_l))
                    alpha_hat = alpha_u - tau * (alpha_u - alpha_l);
                return alpha_hat;
            } // line_search_interpolation
            template <typename X, typename Scalar>
            auto line_search_extrapolation(X &&df_0, X &&df_l, Scalar &&alpha_0, Scalar &&alpha_l, Scalar tau, Scalar chi)
            {
                auto d_alpha_0 = (alpha_0 - alpha_l) * df_0 / (df_l - df_0);
                if (d_alpha_0 < tau * (alpha_0 - alpha_l))
                    d_alpha_0 = tau * (alpha_0 - alpha_l);
                if (d_alpha_0 > chi * (alpha_0 - alpha_l))
                    d_alpha_0 = chi * (alpha_0 - alpha_l);
                auto alpha_hat = alpha_0 + d_alpha_0;
                return alpha_hat;
            }

            /**
             * @brief actual implementation of fibonacci search
             * 
             * @tparam F type of objective function
             * @tparam Scalar real-valued scalar
             * @tparam Sequence container for fibonacci sequence
             * @tparam Logger=std::nullptr_t optional logger type
             * @param f objective function
             * @param x_L0 lower bound
             * @param x_U0 upper bound
             * @param fibo_seq fibonacci sequence
             * @param logger optional logging
             * @return constexpr auto x_opt
             */
            template <typename F, typename Scalar, typename Sequence, typename Logger=std::nullptr_t>
            constexpr auto fibonacci_search(const F &f, const Scalar &x_L0, const Scalar &x_U0, const Sequence& fibo_seq, Logger logger=Logger{})
            {
                auto n = std::size(fibo_seq);
                auto x_L = x_L0;
                auto x_U = x_U0;
                auto I0 = x_U - x_L;
                auto I1 = (Scalar(fibo_seq[n-2]) / Scalar(fibo_seq[n-1])) * I0;
                auto x_a = x_U - I1;
                auto x_b = x_L + I1;
                auto f_a = f(x_a);
                auto f_b = f(x_b);
                for (size_t k=0; k<n-2; k++) {
                    if constexpr (!std::is_same_v<Logger,std::nullptr_t>) {
                        static_assert(std::is_pointer_v<Logger>);
                        (*logger)(std::map<std::string,Scalar>{
                            {"iteration", k}, {"x_a", x_a}, {"x_b", x_b},
                            {"f_a", f_a}, {"f_b", f_b}, {"I", I1}
                        });
                    }
                    auto I2 = (Scalar(fibo_seq[n-(k+1)-2]) / Scalar(fibo_seq[n-(k+1)-1])) * I1;
                    if (f_a >= f_b) {
                        x_L = x_a; x_U = x_U;
                        x_a = x_b; x_b = x_L + I2;
                        f_a = f_b; f_b = f(x_b);
                    } else {
                        x_L = x_L; x_U = x_b;
                        x_b = x_a; x_a = x_U - I2;
                        f_b = f_a; f_a = f(x_a);
                    }
                    if (x_a > x_b)
                        break;
                    I1 = I2;
                }
                return x_a;
            } // fibonacci_search

        } // namespace detail

        template <typename F, typename DF, typename X, typename Scalar>
        auto inexact_line_search(F &&f, DF &&g, X &&xi, X &&d, Scalar alpha_0, Scalar rho, Scalar sigma, Scalar tau, Scalar chi)
        {
            Scalar alpha_l{0};
            Scalar alpha_u{1e99};
            auto gk = g(xi);
            auto f_l = f(xi + alpha_l * d);
            auto df_l = detail::transpose( g(xi + alpha_l * d) ) * d;
            STEP_4 :
            auto f_0 = f(xi+alpha_0*d);
            if (f_0 > f_l + rho * (alpha_0 - alpha_l) * df_l) {
                auto alpha_hat = detail::line_search_interpolation(f_0, f_l, df_l, alpha_0, alpha_u, alpha_l, tau);
                alpha_0 = alpha_hat;
                goto STEP_4;
            }
            auto df_0 = detail::transpose( g(xi + alpha_0 * d) ) * d;
            if (df_0 < sigma * df_l) {
                auto alpha_hat = detail::line_search_extrapolation(df_0, df_l, alpha_0, alpha_l, tau, chi);
                alpha_l = alpha_0;
                alpha_0 = alpha_hat;
                f_l = f_0;
                df_l = df_0;
                goto STEP_4;
            }
            return alpha_0;
        } // inexact_line_search

        /**
         * @brief runtime version of fibonacci search
         * 
         * @tparam F objective function type
         * @tparam Scalar real-valued scalar
         * @tparam Logger=std::nullptr_t optional for logging
         * @param f objective function
         * @param x_L lower bound
         * @param x_U upper bound
         * @param n number of iteration
         * @param logger optional intermediate value logger
         * @return auto optimal x
         * @reference @book{antoniou2007practical,
                title={Practical optimization: algorithms and engineering applications},
                author={Antoniou, Andreas and Lu, Wu-Sheng},
                year={2007},
                publisher={Springer Science \& Business Media}
            }
         */
        template <typename F, typename Scalar, typename Logger=std::nullptr_t>
        auto fibonacci_search(F &&f, Scalar &&x_L, Scalar &&x_U, int n, Logger logger=Logger{})
        {
            /* TODO: unify with constexpr version */

            auto fibo_seq = helper::fibonacci_sequence(n);
            return detail::fibonacci_search(f,x_L,x_U,fibo_seq,logger);
        } // fibonacci_search

        /**
         * @brief constexpr version of fibonacci search,
         * intermediate value loggin not supported at compile time
         * 
         * @tparam n number of iteration
         * @tparam F type of objective function
         * @tparam Scalar real-valued scalar
         * @tparam Logger=std::nullptr_t optional for logging
         * @param f objective function
         * @param x_L lower bound
         * @param x_U upper bound
         * @param logger optional intermediate value logger
         * @return constexpr auto optimal x
         * @reference @book{antoniou2007practical,
                title={Practical optimization: algorithms and engineering applications},
                author={Antoniou, Andreas and Lu, Wu-Sheng},
                year={2007},
                publisher={Springer Science \& Business Media}
            }
         */
        template <size_t n, typename F, typename Scalar, typename Logger=std::nullptr_t>
        constexpr auto fibonacci_search(F &&f, Scalar &&x_L, Scalar &&x_U, Logger logger=Logger{})
        {
            auto fibo_seq = helper::fibonacci_sequence<n>();
            return detail::fibonacci_search(f,x_L,x_U,fibo_seq,logger);
        }
        
    } // namespace optimization
} // namespace nmtools

#endif // NMTOOLS_UNCONSTRAINED_OPTIMIZATION_HPP