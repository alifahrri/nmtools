#ifndef OPEN_ROOTS_HPP
#define OPEN_ROOTS_HPP

#include <cstdio>
#include <cmath>

namespace numeric {
    namespace roots {
        template <typename F, typename G, typename Scalar>
        auto fixed_point(F &f, G &g, Scalar x0, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            xr = x0;
            iter = 0;
            do {
                auto xrold = xr;
                xr = g(xrold);
                iter = iter+1;
                if(std::abs(xr) > zero) {
                    ea = std::abs((xr-xrold)/xr) * Scalar(100.0);
                }
            } while(std::abs(ea) > std::abs(es) &&  iter < imax);
        }

        template <typename F, typename DF, typename Scalar>
        auto newton_raphson(F &f, DF &df, Scalar x0, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            auto g = [&f,&df](Scalar x){
                return (x-(f(x)/df(x)));
            };
            fixed_point(f,g,x0,xr,es,imax,iter,ea,zero);
        }
    } // namespace roots
} // namespace numeric
#endif // OPEN_ROOTS_HPP