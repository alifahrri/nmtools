#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct minimum_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t < u ? t : u;
        } // operator()
    }; // minimum_t

    template <typename left_t, typename right_t>
    constexpr auto minimum(const left_t& a, const right_t& b)
    {
        return ufunc(minimum_t{},a,b);
    } // minimum
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP