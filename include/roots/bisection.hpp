#ifndef BISECTION_HPP
#define BISECTION_HPP

#include <cstdio>
#include <cmath>

namespace numeric {
    namespace roots {
        namespace detail {
            template <typename F, typename Scalar, typename RootEstimator>
            auto closed_method(
                F& f, 
                Scalar xu, Scalar xl, 
                Scalar es, 
                Scalar &xr,
                size_t imax, size_t &iter, 
                Scalar &ea, 
                Scalar zero,
                RootEstimator &estimator)
            {
                iter = 0; ea = Scalar(100.0);
                do {
                    auto xrold = xr;
                    // xr = (xl + xu) / 2;
                    xr = estimator(f, xl, xu);
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
            auto root_estimator = [](F& f, Scalar xl, Scalar xu) {
                return (xl+xu)/2;
            };
            detail::closed_method(f, xu, xl, es, xr, imax, iter, ea, zero, root_estimator);
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
            auto root_estimator = [](F& f, Scalar xl, Scalar xu) {
                return (xu - (f(xu) * (xl-xu)) / (f(xl)-f(xu)));
            };
            detail::closed_method(f, xu, xl, es, xr, imax, iter, ea, zero, root_estimator);
        }
    }
}

#endif // BISECTION_HPP