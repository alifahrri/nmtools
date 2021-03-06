#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct exp2_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::exp2(t);
        } // operator()
    }; // exp2_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto exp2(const left_t& a)
    {
        return ufunc(exp2_t{},a);
    } // exp2
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP