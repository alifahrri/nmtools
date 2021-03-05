#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct trunc_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::trunc(t);
        } // operator()
    }; // trunc_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto trunc(const left_t& a)
    {
        return ufunc(trunc_t{},a);
    } // trunc
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP