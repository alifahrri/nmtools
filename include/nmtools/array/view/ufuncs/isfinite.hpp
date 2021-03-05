#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct isfinite_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::isfinite(t);
        } // operator()
    }; // isfinite_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto isfinite(const left_t& a)
    {
        return ufunc(isfinite_t{},a);
    } // isfinite
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP