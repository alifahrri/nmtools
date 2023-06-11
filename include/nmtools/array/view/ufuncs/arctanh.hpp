#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct arctanh_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::atanh(t);
        } // operator()
    }; // arctanh_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctanh(const left_t& a)
    {
        return ufunc(arctanh_t{},a);
    } // arctanh
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP