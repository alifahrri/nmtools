#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct arctan_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::atan(t);
        } // operator()
    }; // arctan_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctan(const left_t& a)
    {
        return ufunc(arctan_t{},a);
    } // arctan
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP