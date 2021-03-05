#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct rint_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return std::rint(t);
        } // operator()
    }; // rint_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto rint(const left_t& a)
    {
        return ufunc(rint_t{},a);
    } // rint
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP