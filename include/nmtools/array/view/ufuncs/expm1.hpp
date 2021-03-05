#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct expm1_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::expm1(t);
        } // operator()
    }; // expm1_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto expm1(const left_t& a)
    {
        return ufunc(expm1_t{},a);
    } // expm1
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP