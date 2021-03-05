#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct isinf_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::isinf(t);
        } // operator()
    }; // isinf_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto isinf(const left_t& a)
    {
        return ufunc(isinf_t{},a);
    } // isinf
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP