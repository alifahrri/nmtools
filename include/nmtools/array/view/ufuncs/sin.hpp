#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct sin_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sin(t);
        } // operator()
    }; // sin_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sin(const left_t& a)
    {
        return ufunc(sin_t{},a);
    } // sin
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP