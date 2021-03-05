#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct reciprocal_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return 1/t;
        } // operator()
    }; // reciprocal_t

    template <typename left_t>
    constexpr auto reciprocal(const left_t& a)
    {
        return ufunc(reciprocal_t{},a);
    } // reciprocal
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP