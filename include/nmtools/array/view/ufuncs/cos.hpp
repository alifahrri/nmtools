#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct cos_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::cos(t);
        } // operator()
    }; // cos_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto cos(const left_t& a)
    {
        return ufunc(cos_t{},a);
    } // cos
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP