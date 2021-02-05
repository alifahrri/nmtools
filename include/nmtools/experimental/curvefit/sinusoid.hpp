#ifndef NMTOOLS_SINUSOID_HPP
#define NMTOOLS_SINUSOID_HPP

#include <iterator>
#include <cmath>
#include <tuple>

namespace nmtools::curvefit {

    /**
     * @brief curve fitting with sinusoidal function for periodic function
     *  y = A_0 + A_1 cos(\omega_0 t) + B_1 sin(\omega_0 t)
     * @tparam Ts 
     * @tparam Ys 
     * @tparam Scalar real numbers
     * @param ts index sequence
     * @param ys value sequence
     * @param omega frequency coefficients
     * @return constexpr auto [A0, A1, B1]
     * @reference Sec. curve fitting with sinusoidal function, Ch. Fourier Approximation 
     *      @book{Chapra2010,
                author = {Chapra, Steven C and Canale, Raymond P},
                title = {{Numerical Methods for Engineers Sixth Edition Chapra Canale}},
            } 
     */
    template <typename Ts, typename Ys, typename Scalar>
    constexpr auto sinusoid(const Ts &ts, const Ys &ys, Scalar omega) 
    {
        /* TODO : support C++14 and lower (?) */
        auto n = std::size(ts);
        auto sum_y = Scalar{0};
        auto sum_c = Scalar{0};
        auto sum_s = Scalar{0};
        auto t_iter = std::begin(ts);
        auto y_iter = std::begin(ys);
        // auto t_end = std::end(ts);
        // auto y_end = std::end(ys);
        for (size_t i=0; i<n; i++) {
            sum_y += *y_iter;
            sum_c += *y_iter * cos(omega*(*t_iter));
            sum_s += *y_iter * sin(omega*(*t_iter));
            y_iter++;
            t_iter++;
        }
        auto A0 = sum_y / n;
        auto A1 = 2 * sum_c / n;
        auto B1 = 2 * sum_s / n;
        return std::make_tuple(A0,A1,B1);
    }

} // namespace nmtools::curvefit

#endif // NMTOOLS_SINUSOID_HPP