#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct fmax_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return std::fmax(t,u);
        } // operator()
    }; // fmax_t

    template <typename rhs_t>
    struct fmax_t<none_t,none_t,rhs_t,
        std::enable_if_t<std::is_arithmetic_v<rhs_t>>
    >
    {
        using result_type = rhs_t;

        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const -> rhs_t
        {
            return std::fmax(t,u);
        } // operator()
    }; // fmax_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmax(const left_t& a, const right_t& b)
    {
        return ufunc(fmax_t<>{},a,b);
    } // fmax

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmax(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t init)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmax_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,init);
    } // reduce_fmax

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmax(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_fmax(a,axis,dtype,None);
    } // reduce_fmax

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmax(const left_t& a, const axis_t& axis)
    {
        return reduce_fmax(a,axis,None,None);
    } // reduce_fmax
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP