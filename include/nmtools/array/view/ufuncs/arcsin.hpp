#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct arcsin_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::asin(t);
        } // operator()
    }; // arcsin_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto arcsin(const left_t& a)
    {
        return ufunc(arcsin_t{},a);
    } // arcsin
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP