#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct hypot_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::hypot(t,u);
        } // operator()
    }; // hypot_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto hypot(const left_t& a, const right_t& b)
    {
        return ufunc(hypot_t{},a,b);
    } // hypot
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP