#ifndef UNCONSTRAINED_OPTIMIZATION_HPP
#define UNCONSTRAINED_OPTIMIZATION_HPP

#include <cstdio>
#include <cmath>
#include <tuple>
#include <functional>

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
        
    } // namespace optimization
} // namespace numeric

#endif // UNCONSTRAINED_OPTIMIZATION_HPP