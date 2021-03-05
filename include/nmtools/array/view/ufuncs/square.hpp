#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct square_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return t * t;
        } // operator()
    }; // square_t

    template <typename left_t>
    constexpr auto square(const left_t& a)
    {
        return ufunc(square_t{},a);
    } // square
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP