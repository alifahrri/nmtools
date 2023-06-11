#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct tan_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::tan(t);
        } // operator()
    }; // tan_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tan(const left_t& a)
    {
        return ufunc(tan_t{},a);
    } // tan
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP