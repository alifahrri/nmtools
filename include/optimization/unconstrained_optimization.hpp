#ifndef UNCONSTRAINED_OPTIMIZATION_HPP
#define UNCONSTRAINED_OPTIMIZATION_HPP

#include <cstdio>
#include <cmath>
#include <functional>

namespace numeric {
    namespace optimization {
        template <typename F, typename Scalar, template<typename> Op = std::greater>
        auto gold_section(F &f, Scalar xlow, Scalar xhigh, Scalar &xopt, size_t imax, size_t &iter, Scalar es, Scalar fx) {
            constexpr Scalar R = (std::sqrt(Scalar(5))-1)/2;
            auto xl = xlow; auto xh = xhigh;
            iter = 1;
            auto d = R * (xu - xl);
            auto x1 = xl + d; auto x2 = xu - d;
            auto f1 = f(x1);
            auto f2 = f(x2);
            if(Op(f1,f2)) {
                xopt = x1;
                fx = f1;
            } else {
                xopt = x2;
                fx = f2;
            }
            do {
                d = R * d; auto xint = xu -xl;
                if(Op(f1,f2)) {
                    xl = x2;
                    x2 = x1;
                    x1 = xl + d;
                    f2 = f1;
                    f1 = f(x1);
                } else {
                    xu = x1;
                    x1 = x2;
                    x2 = xu - d;
                    f1 = f2;
                    f2 = f(x2);
                }
                iter = iter + 1;
                if(Op(f1,f2)) {
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