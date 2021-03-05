#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct logical_not_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return !static_cast<bool>(t);
        } // operator()
    }; // logical_not_t

    template <typename left_t>
    constexpr auto logical_not(const left_t& a)
    {
        return ufunc(logical_not_t{},a);
    } // logical_not
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP