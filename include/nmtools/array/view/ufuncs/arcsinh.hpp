#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct arcsinh_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::asinh(t);
        } // operator()
    }; // arcsinh_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto arcsinh(const left_t& a)
    {
        return ufunc(arcsinh_t{},a);
    } // arcsinh
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP