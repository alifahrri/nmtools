#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct cosh_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::cosh(t);
        } // operator()
    }; // cosh_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto cosh(const left_t& a)
    {
        return ufunc(cosh_t{},a);
    } // cosh
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP