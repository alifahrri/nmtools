#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct arctan2_t
    {
        template <typename T, typename U>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::atan2(t,u);
        } // operator()
    }; // arctan2_t

    template <typename left_t, typename right_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctan2(const left_t& a, const right_t& b)
    {
        return ufunc(arctan2_t{},a,b);
    } // arctan2
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP