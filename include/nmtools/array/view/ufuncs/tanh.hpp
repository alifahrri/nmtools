#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct tanh_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::tanh(t);
        } // operator()
    }; // tanh_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tanh(const left_t& a)
    {
        return ufunc(tanh_t{},a);
    } // tanh
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP