#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct positive_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return +t;
        } // operator()
    }; // positive_t

    template <typename left_t>
    constexpr auto positive(const left_t& a)
    {
        return ufunc(positive_t{},a);
    } // positive
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP