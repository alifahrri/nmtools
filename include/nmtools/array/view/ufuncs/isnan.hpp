#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct isnan_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::isnan(t);
        } // operator()
    }; // isnan_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto isnan(const left_t& a)
    {
        return ufunc(isnan_t{},a);
    } // isnan
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP