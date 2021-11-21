#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct exp_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::exp(t);
        } // operator()
    }; // exp_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto exp(const left_t& a)
    {
        return ufunc(exp_t{},a);
    } // exp
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP