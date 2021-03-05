#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct power_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return std::pow(t,u);
        } // operator()
    }; // power_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto power(const left_t& a, const right_t& b)
    {
        return ufunc(power_t{},a,b);
    } // power
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP