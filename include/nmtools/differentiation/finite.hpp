#ifndef NMTOOLS_FINITE_HPP
#define NMTOOLS_FINITE_HPP

#include <cmath>

namespace nmtools::differentiation {

    enum class Formulas {
        Centered,
        Forward,
        Backward  
    };

    /* workaround for function template partial specialization */
    namespace detail
    {
        /* TODO: add second order differentiation */
        template <size_t order>
        struct Order{};
        template <Formulas fomula>
        struct ComputeType{};

        template <typename F, typename Scalar>
        constexpr auto finite_difference(Order<1>, ComputeType<Formulas::Forward>, F &f, Scalar x, Scalar step)
        {
            const auto& h = step; // alias
            return (-f(x+2*h) + 4*f(x+h) - 3*f(x)) / (2*h);
        }

        template <typename F, typename Scalar>
        constexpr auto finite_difference(Order<1>, ComputeType<Formulas::Backward>, F &f, Scalar x, Scalar step)
        {
            const auto& h = step; // alias
            return ((3*f(x)) - 4*f(x-h) + f(x-2*h)) / (2*h);
        }

        template <typename F, typename Scalar>
        constexpr auto finite_difference(Order<1>, ComputeType<Formulas::Centered>, F &f, Scalar x, Scalar step)
        {
            const auto& h = step; // alias
            return (-f(x+2*h) + 8*f(x+h) - 8*f(x-h) + f(x-2*h)) / (12*h);
        }
    } // namespace detail
    
    template <size_t order=1, Formulas formula=Formulas::Centered, typename F, typename Scalar>
    constexpr auto finite_difference(F &f, Scalar x, Scalar step)
    {
        return detail::finite_difference(detail::Order<order>{}, detail::ComputeType<formula>{}, f, x, step);
    }
    
} // namespace nmtools
#endif // NMTOOLS_FINITE_HPP