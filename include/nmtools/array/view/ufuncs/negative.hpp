#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct negative_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return -t;
        } // operator()
    }; // negative_t

    template <typename left_t>
    constexpr auto negative(const left_t& a)
    {
        return ufunc(negative_t{},a);
    } // negative
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP