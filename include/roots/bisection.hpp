#ifndef BISECTION_HPP
#define BISECTION_HPP

#include <cstdio>
#include <cmath>

namespace numeric {
    namespace roots {
        template <typename F, typename Scalar>
        auto bisection(
            F& f, 
            Scalar xu, 
            Scalar xl, 
            Scalar es, 
            Scalar &xr,
            size_t imax, 
            size_t &iter, 
            Scalar &ea, 
            Scalar zero = Scalar(1e-6)) 
        {
            iter = 0; ea = Scalar(100.0);
            do {
                auto xrold = xr;
                xr = (xl + xu) / 2;
                iter = iter + 1;
                if((std::abs(xr) > zero) && (iter > 1)) {
                    ea = std::abs((xr-xrold) / xr) * Scalar(100.0);
                }
                auto test = f(xl) * f(xr);
                if(test < zero) {
                    xu = xr;
                } else if(test > zero) {
                    xl = xr;
                } else {
                    ea = zero;
                }
            } while(std::abs(ea) > std::abs(es) && iter < imax);
        }

        template <typename F, typename Scalar>
        auto false_position(
            F& f, 
            Scalar xu, 
            Scalar xl, 
            Scalar es, 
            Scalar &xr,
            size_t imax, 
            size_t &iter, 
            Scalar &ea, 
            Scalar zero = Scalar(1e-6)) 
        {
            iter = 0; ea = Scalar(100.0);
            do {
                auto xrold = xr;
                xr = xu - (f(xu) * (xl-xu)) / (f(xl)-f(xu));
                iter = iter + 1;
                if((std::abs(xr) > zero) && (iter > 1)) {
                    ea = std::abs((xr-xrold) / xr) * Scalar(100.0);
                }
                auto test = f(xl) * f(xr);
                if(test < zero) {
                    xu = xr;
                } else if(test > zero) {
                    xl = xr;
                } else {
                    ea = zero;
                }
            } while(std::abs(ea) > std::abs(es) && iter < imax);
        }
    }
}

#endif // BISECTION_HPP