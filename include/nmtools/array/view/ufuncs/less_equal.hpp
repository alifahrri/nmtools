#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct less_equal_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t <= u;
        } // operator()
    }; // less_equal_t

    template <typename left_t, typename right_t>
    constexpr auto less_equal(const left_t& a, const right_t& b)
    {
        return ufunc(less_equal_t{},a,b);
    } // less_equal
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP