#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct log1p_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log1p(t);
        } // operator()
    }; // log1p_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log1p(const left_t& a)
    {
        return ufunc(log1p_t{},a);
    } // log1p
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP