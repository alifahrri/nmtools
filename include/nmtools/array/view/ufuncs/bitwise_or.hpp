#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct bitwise_or_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t | u;
        } // operator()
    }; // bitwise_or_t

    template <typename left_t, typename right_t>
    constexpr auto bitwise_or(const left_t& a, const right_t& b)
    {
        return ufunc(bitwise_or_t{},a,b);
    } // bitwise_or
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_BITWISE_OR_HPP