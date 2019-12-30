#ifndef NMTOOLS_FOURIER_SERIES_HPP
#define NMTOOLS_FOURIER_SERIES_HPP

#include <iterator>
#include <cmath>
#include "nmtools/integration.hpp"

namespace nmtools {
    namespace fourier {
        namespace detail {
            template <typename F, typename Scalar>
            constexpr Scalar(*integrator)(const F&,Scalar,Scalar,size_t) = &integration::trapezoid<F,Scalar>;
        }
        template <size_t nsegments = 100, typename F, typename As, typename Bs, typename Scalar = decltype(*std::begin(std::declval<As>()))>
        void series(F &f, Scalar T, Scalar &a0, As &a, Bs &b) {
            assert(std::size(a)==std::size(b));
            auto n = std::size(a);
            auto a_iter = std::begin(a);
            auto b_iter = std::begin(b);
            a0 = detail::integrator<F,Scalar>(f,Scalar{0},T,nsegments) / T;
            auto freq = 2*M_PI/T;
            for (size_t i=0; i<n; i++) {
                auto fc = [f, k=i+1, w=freq](Scalar t) {
                    return f(t)*cos(k*w*t);
                };
                auto fs = [f, k=i+1, w=freq](Scalar t) {
                    return f(t)*sin(k*w*t);
                };
                *a_iter = 2. * detail::integrator<decltype(fc),Scalar>(fc,Scalar{0},T,nsegments) / T;
                *b_iter = 2. * detail::integrator<decltype(fs),Scalar>(fs,Scalar{0},T,nsegments) / T;
                a_iter++; b_iter++;
            }
        }
    } // namespace fourier
} // namespace nmtools

#endif // NMTOOLS_FOURIER_SERIES_HPP