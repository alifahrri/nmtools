#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct ceil_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::ceil(t);
        } // operator()
    }; // ceil_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto ceil(const left_t& a)
    {
        return ufunc(ceil_t{},a);
    } // ceil
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP