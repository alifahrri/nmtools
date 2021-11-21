#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct arccos_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::acos(t);
        } // operator()
    }; // arccos_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto arccos(const left_t& a)
    {
        return ufunc(arccos_t{},a);
    } // arccos
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP