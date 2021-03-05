#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct invert_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return ~t;
        } // operator()
    }; // invert_t

    template <typename left_t>
    constexpr auto invert(const left_t& a)
    {
        return ufunc(invert_t{},a);
    } // invert
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP