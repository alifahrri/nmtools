#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct minimum_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t < u ? t : u;
        } // operator()
    }; // minimum_t

    template <typename res_t>
    struct minimum_t<none_t,none_t,res_t
        , std::enable_if_t<std::is_arithmetic_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t < u ? t : u;
        } // operator()
    }; // minimum_t

    template <typename left_t, typename right_t>
    constexpr auto minimum(const left_t& a, const right_t& b)
    {
        return ufunc(minimum_t<>{},a,b);
    } // minimum

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto reduce_minimum(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = minimum_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,None);
    } // reduce_minimum

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto reduce_minimum(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_minimum(a,axis,dtype,None);
    } // reduce_minimum

    template <typename left_t, typename axis_t>
    constexpr auto reduce_minimum(const left_t& a, const axis_t& axis)
    {
        return reduce_minimum(a,axis,None,None);
    } // reduce_minimum
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP