#ifndef NMTOOLS_TRAPEZOIDAL_HPP
#define NMTOOLS_TRAPEZOIDAL_HPP

#include <cstdio>

namespace nmtools
{
    namespace integration 
    {
        namespace detail {
            template <typename F, typename Scalar>
            constexpr Scalar trapezoid(const F &f, Scalar a, Scalar b, size_t n_segments)
            {
                Scalar step = (b-a) / n_segments;
                Scalar sum = f(a);
                for(size_t i=1; i<n_segments; i++)
                    sum += 2 * f(a+i*step);
                sum += f(a+n_segments*step);
                return step * sum / 2;
            }
        }
        template <typename F, typename Scalar>
        void trapezoid(const F &f, Scalar a, Scalar b, size_t n_segments, Scalar &I)
        {
            I = detail::trapezoid(f,a,b,n_segments);
        }
        template <typename F, typename Scalar>
        constexpr Scalar trapezoid(const F& f, Scalar a, Scalar b, size_t n_segment)
        {
            return detail::trapezoid(f,a,b,n_segment);
        }
        template <size_t n_segments, typename F, typename Scalar>
        void trapezoid(const F &f, Scalar a, Scalar b, Scalar &I)
        {
            Scalar step = (b-a) / n_segments;
            Scalar sum = f(a);
            for(size_t i=1; i<n_segments; i++)
                sum += 2 * f(a+i*step);
            sum += f(a+n_segments*step);
            I = step * sum / 2;
        }
    } // namespace integration
} // namespace nmtools
#endif // NMTOOLS_TRAPEZOIDAL_HPP