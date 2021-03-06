#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct fabs_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::fabs(t);
        } // operator()
    }; // fabs_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fabs(const left_t& a)
    {
        return ufunc(fabs_t{},a);
    } // fabs
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP