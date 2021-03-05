#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMIN_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct fmin_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return std::fmin(t,u);
        } // operator()
    }; // fmin_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmin(const left_t& a, const right_t& b)
    {
        return ufunc(fmin_t{},a,b);
    } // fmin
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMIN_HPP