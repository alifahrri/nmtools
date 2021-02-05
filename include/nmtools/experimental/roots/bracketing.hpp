#ifndef NMTOOLS_BISECTION_HPP
#define NMTOOLS_BISECTION_HPP

#include <cstdio>
#include <cmath>

namespace nmtools {
    namespace roots {
        namespace detail {
            template <typename F, typename Scalar, typename RootEstimator>
            auto bracketing(
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
                    if(test < -zero) {
                        xu = xr;
                    } else if(test > zero) {
                        xl = xr;
                    } else {
                        ea = zero;
                    }
                } while(std::abs(ea) > std::abs(es) && iter < imax);
            }
        } // namespace detail

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
            detail::bracketing(f, xu, xl, es, xr, imax, iter, ea, zero, root_estimator);
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
            detail::bracketing(f, xu, xl, es, xr, imax, iter, ea, zero, root_estimator);
        }

        template <typename F, typename Scalar>
        auto modified_false_position(
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
            iter = 0;
            auto fl = f(xl);
            auto fu = f(xu);
            size_t iu{0}, il{0};
            do {
                auto xrold = xr;
                xr = xu - fu * (xl - xu) / (fl - fu);
                auto fr = f(xr);
                iter = iter + 1;
                if(std::abs(xr) > zero) {
                    ea = std::abs((xr-xrold)/xr) * Scalar(100.0);
                }
                auto test = fl * fr;
                if(test < -zero) {
                    xu = xr;
                    fu = f(xu);
                    iu = 0;
                    il = il + 1;
                    if(il >= 2) {
                        fl = fl/2;
                    }
                } else if(test > zero) {
                    xl = xr;
                    fl = f(xl);
                    il = 0;
                    iu = iu + 1;
                    if(iu >= 2) {
                        fu = fu/2;
                    }
                } else {
                    ea = zero;
                }
            } while(std::abs(ea) > std::abs(es) && iter < imax);
        }
    } // namespace roots
} // namespace nmtools

#endif // NMTOOLS_BISECTION_HPP