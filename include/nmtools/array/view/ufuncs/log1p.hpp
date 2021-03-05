#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct log1p_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::log1p(t);
        } // operator()
    }; // log1p_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto log1p(const left_t& a)
    {
        return ufunc(log1p_t{},a);
    } // log1p
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP