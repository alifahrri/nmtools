#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct subtract_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t - u;
        } // operator()
    }; // subtract_t

    template <typename left_t, typename right_t>
    constexpr auto subtract(const left_t& a, const right_t& b)
    {
        return ufunc(subtract_t{},a,b);
    } // subtract
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP