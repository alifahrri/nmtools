#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    template <
        typename lhs_t=none_t, typename rhs_t=none_t,
        typename res_t=none_t, typename=void>
    struct power_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return std::pow(t,u);
        } // operator()
    }; // power_t

    template <typename res_t>
    struct power_t<none_t,none_t,res_t,
        std::enable_if_t<(!is_none_v<res_t>)>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const -> res_t
        {
            return std::pow(t,u);
        } // operator()
    }; // power_t

    template <typename lhs_t, typename rhs_t, typename res_t>
    struct power_t<lhs_t,rhs_t,res_t,std::enable_if_t<
        (!is_none_v<lhs_t>) && (!is_none_v<rhs_t>) && (!is_none_v<res_t>)
    >>
    {
        using result_type = res_t;

        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const lhs_t& t, const rhs_t& u) const -> res_t
        {
            return std::pow(t,u);
        } // operator()
    }; // power_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto power(const left_t& a, const right_t& b)
    {
        return ufunc(power_t<>{},a,b);
    } // power

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_power(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        static_assert( std::is_integral_v<axis_t>
            , "reduce_power only support single axis with integral type"
        );
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = power_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,initial);
    } // reduce_power

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_power(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        static_assert( std::is_integral_v<axis_t>
            , "reduce_power only support single axis with integral type"
        );
        using res_t = get_dtype_t<dtype_t>;
        using op_t = power_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,None);
    } // reduce_power

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_power(const left_t& a, const axis_t& axis)
    {
        return reduce_power(a,axis,None);
    } // reduce_power
}

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP