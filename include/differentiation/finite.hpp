#ifndef FINITE_HPP
#define FINITE_HPP

#include <cmath>

namespace numeric {
    namespace differentiation {

        enum class Formulas {
            Centered,
            Forward,
            Backward  
        };

        /* workaround for function template partial specialization */
        namespace detail
        {
            template <size_t order>
            struct Order{};
            template <Formulas fomula>
            struct ComputeType{};

            template <typename F, typename Scalar>
            void finite_difference(Order<1>, ComputeType<Formulas::Forward>, F &f, Scalar x, Scalar step, Scalar &d)
            {
                const auto& h = step;
                d = (-f(x+2*h) + 4*f(x+h) - 3*f(x)) / (2*h);
            }

            template <typename F, typename Scalar>
            void finite_difference(Order<1>, ComputeType<Formulas::Backward>, F &f, Scalar x, Scalar step, Scalar &d)
            {
                const auto& h = step;
                d = ((3*f(x)) - 4*f(x-h) + f(x-2*h)) / (2*h);
            }

            template <typename F, typename Scalar>
            void finite_difference(Order<1>, ComputeType<Formulas::Centered>, F &f, Scalar x, Scalar step, Scalar &d)
            {
                const auto& h = step;
                d = (-f(x+2*h) + 8*f(x+h) - 8*f(x-h) + f(x-2*h)) / (12*h);
            }
        } // namespace detail
        
        template <size_t order, Formulas formula = Formulas::Centered, typename F, typename Scalar>
        void finite_difference(F &f, Scalar x, Scalar step, Scalar &d)
        {
            detail::finite_difference(detail::Order<order>{}, detail::ComputeType<formula>{}, f, x, step, d);
        }

        /* unfortunately, we cant do this */
        #if 0
        template <typename F, typename Scalar>
        void finite_difference<1,Formulas::Forward,F,Scalar>(F &f, Scalar x, Scalar step, Scalar &d)
        {
            const auto& h = step;
            d = (-f(x+2*h) + 4*f(x+h) - 3*f(x))/(2*h);
        }
        template <typename F, typename Scalar>
        void finite_difference<1,Formulas::Backward,F,Scalar>(F &f, Scalar x, Scalar step, Scalar &d)
        {
            const auto& h = step;
            d = ((3*f(x)) - 4*f(x-h) + -f(x-2*h))/(2*h);
        }
        template <typename F, typename Scalar>
        void finite_difference<1,Formulas::Centered,F,Scalar>(F &f, Scalar x, Scalar step, Scalar &d)
        {
            const auto& h = step;
            d = (-f(x+2*h) + 8*f(x+h) - 8*f(x-h) + f(x-2*h))/(2*h);
        }
        #endif
    } // namespace differentiation
} // namespace numeric
#endif // FINITE_HPP