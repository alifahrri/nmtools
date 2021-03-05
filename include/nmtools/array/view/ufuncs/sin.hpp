#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct sin_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::sin(t);
        } // operator()
    }; // sin_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto sin(const left_t& a)
    {
        return ufunc(sin_t{},a);
    } // sin
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP