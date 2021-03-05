#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct log10_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::log10(t);
        } // operator()
    }; // log10_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto log10(const left_t& a)
    {
        return ufunc(log10_t{},a);
    } // log10
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP