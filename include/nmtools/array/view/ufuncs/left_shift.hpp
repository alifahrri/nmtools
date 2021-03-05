#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LEFT_SHIFT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LEFT_SHIFT_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct left_shift_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t << u;
        } // operator()
    }; // left_shift_t

    template <typename left_t, typename right_t>
    constexpr auto left_shift(const left_t& a, const right_t& b)
    {
        return ufunc(left_shift_t{},a,b);
    } // left_shift
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LEFT_SHIFT_HPP