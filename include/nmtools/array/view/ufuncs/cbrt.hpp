#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct cbrt_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::cbrt(t);
        } // operator()
    }; // cbrt_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto cbrt(const left_t& a)
    {
        return ufunc(cbrt_t{},a);
    } // cbrt
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP