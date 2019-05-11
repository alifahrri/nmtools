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

        template <typename F, typename Scalar>
        auto secant(F &f, Scalar x0, Scalar x_1, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            auto g = [&f,&x_1](Scalar x){
                auto xr = (x-(f(x)*(x_1-x)/(f(x_1)-f(x))));
                x_1 = x;
                return xr;
            };
            fixed_point(f,g,x0,xr,es,imax,iter,ea,zero);
        }

        template <typename F, typename Scalar>
        auto modified_secant(F &f, Scalar x0, Scalar delta, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            auto g = [&f,delta](Scalar x){
                return (x-(delta*f(x)/(f(x+delta)-f(x))));
            };
            fixed_point(f,g,x0,xr,es,imax,iter,ea,zero);
        }
    } // namespace roots
} // namespace numeric
#endif // OPEN_ROOTS_HPP