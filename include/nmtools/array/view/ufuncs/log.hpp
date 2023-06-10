#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    struct log_t
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log(t);
        } // operator()
    }; // log_t

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log(const left_t& a)
    {
        return ufunc(log_t{},a);
    } // log
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP