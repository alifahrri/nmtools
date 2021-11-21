#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct log2_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log2(t);
        } // operator()
    }; // log2_t

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto log2(const left_t& a)
    {
        return ufunc(log2_t{},a);
    } // log2
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP