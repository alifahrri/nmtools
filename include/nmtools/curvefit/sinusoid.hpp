#ifndef NMTOOLS_SINUSOID_HPP
#define NMTOOLS_SINUSOID_HPP

#include <iterator>
#include <cmath>

namespace nmtools {
    namespace curvefit {

        template <typename Ts, typename Ys, typename Scalar = decltype(*std::begin(std::declval<Ys>()))>
        void sinusoid(const Ts &ts, const Ys &ys, Scalar omega, Scalar &A0, Scalar &A1, Scalar &B1) {
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
            A0 = sum_y / n;
            A1 = 2 * sum_c / n;
            B1 = 2 * sum_s / n;
        }

    } // namespace curvefit
} // namespace nmtools

#endif // NMTOOLS_SINUSOID_HPP