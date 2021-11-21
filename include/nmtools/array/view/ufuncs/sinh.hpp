#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct sinh_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sinh(t);
        } // operator()
    }; // sinh_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto sinh(const left_t& a)
    {
        return ufunc(sinh_t{},a);
    } // sinh
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP