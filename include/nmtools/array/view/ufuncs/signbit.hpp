#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct signbit_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::signbit(t);
        } // operator()
    }; // signbit_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto signbit(const left_t& a)
    {
        return ufunc(signbit_t{},a);
    } // signbit
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP