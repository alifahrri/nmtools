#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct greater_equal_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t >= u;
        } // operator()
    }; // greater_equal_t

    template <typename left_t, typename right_t>
    constexpr auto greater_equal(const left_t& a, const right_t& b)
    {
        return ufunc(greater_equal_t{},a,b);
    } // greater_equal
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP