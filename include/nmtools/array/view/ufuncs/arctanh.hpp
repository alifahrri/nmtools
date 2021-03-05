#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct arctanh_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return std::atanh(t);
        } // operator()
    }; // arctanh_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctanh(const left_t& a)
    {
        return ufunc(arctanh_t{},a);
    } // arctanh
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP