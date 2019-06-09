#ifndef TRAPEZOIDAL_HPP
#define TRAPEZOIDAL_HPP

#include <cstdio>

namespace numeric
{
    namespace integration 
    {
        template <typename F, typename Scalar>
        void trapezoid(F &f, Scalar a, Scalar b, size_t n_segments, Scalar &I)
        {
            Scalar step = (b-a) / n_segments;
            Scalar sum = f(a);
            for(size_t i=1; i<n_segments; i++)
                sum += 2 * f(a+i*step);
            sum += f(a+n_segments*step);
            I = step * sum / 2;
        }
        template <size_t n_segments, typename F, typename Scalar>
        void trapezoid(F &f, Scalar a, Scalar b, Scalar &I)
        {
            Scalar step = (b-a) / n_segments;
            Scalar sum = f(a);
            for(size_t i=1; i<n_segments; i++)
                sum += 2 * f(a+i*step);
            sum += f(a+n_segments*step);
            I = step * sum / 2;
        }
    } // namespace integration
} // namespace numeric
#endif // TRAPEZOIDAL_HPP