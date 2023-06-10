#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct arcsin_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::asin(t);
        } // operator()
    }; // arcsin_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arcsin(const left_t& a)
    {
        return ufunc(arcsin_t{},a);
    } // arcsin
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP