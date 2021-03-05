#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct floor_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::floor(t);
        } // operator()
    }; // floor_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto floor(const left_t& a)
    {
        return ufunc(floor_t{},a);
    } // floor
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP