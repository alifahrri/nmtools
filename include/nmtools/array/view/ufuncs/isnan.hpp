#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct isnan_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::isnan(t);
        } // operator()
    }; // isnan_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto isnan(const left_t& a)
    {
        return ufunc(isnan_t{},a);
    } // isnan
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP