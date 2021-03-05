#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MAXIMUM_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MAXIMUM_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct maximum_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t > u ? t : u;
        } // operator()
    }; // maximum_t

    template <typename left_t, typename right_t>
    constexpr auto maximum(const left_t& a, const right_t& b)
    {
        return ufunc(maximum_t{},a,b);
    } // maximum
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MAXIMUM_HPP