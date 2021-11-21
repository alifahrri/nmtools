#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct ldexp_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::ldexp(t,u);
        } // operator()
    }; // ldexp_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto ldexp(const left_t& a, const right_t& b)
    {
        return ufunc(ldexp_t{},a,b);
    } // ldexp
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP