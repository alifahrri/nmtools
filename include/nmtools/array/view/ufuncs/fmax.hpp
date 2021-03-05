#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct fmax_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return std::fmax(t,u);
        } // operator()
    }; // fmax_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmax(const left_t& a, const right_t& b)
    {
        return ufunc(fmax_t{},a,b);
    } // fmax
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP