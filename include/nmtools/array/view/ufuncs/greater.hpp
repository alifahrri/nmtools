#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct greater_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t > u;
        } // operator()
    }; // greater_t

    template <typename left_t, typename right_t>
    constexpr auto greater(const left_t& a, const right_t& b)
    {
        return ufunc(greater_t{},a,b);
    } // greater
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP