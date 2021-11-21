#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct arccosh_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::acosh(t);
        } // operator()
    }; // arccosh_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto arccosh(const left_t& a)
    {
        return ufunc(arccosh_t{},a);
    } // arccosh
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP