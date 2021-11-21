#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SQRT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SQRT_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct sqrt_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sqrt(t);
        } // operator()
    }; // sqrt_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto sqrt(const left_t& a)
    {
        return ufunc(sqrt_t{},a);
    } // sqrt
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SQRT_HPP