#ifndef UNCONSTRAINED_OPTIMIZATION_HPP
#define UNCONSTRAINED_OPTIMIZATION_HPP

#include <cstdio>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <functional>
#include "utility.hpp"

namespace numeric {
    namespace optimization {
        namespace detail {
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
        }
    } // namespace optimization
} // namespace numeric

#endif // UNCONSTRAINED_OPTIMIZATION_HPP