#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct subtract_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t - u;
        } // operator()
    }; // subtract_t

    template <typename res_t>
    struct subtract_t<none_t,none_t,res_t
        , std::enable_if_t<std::is_arithmetic_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t - u;
        } // operator()
    }; // subtract_t

    template <typename left_t, typename right_t>
    constexpr auto subtract(const left_t& a, const right_t& b)
    {
        return ufunc(subtract_t<>{},a,b);
    } // subtract

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto reduce_subtract(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        static_assert( std::is_integral_v<axis_t>
            , "reduce_subtract only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_subtract only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = subtract_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,initial);
    } // reduce_subtract

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto reduce_subtract(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_subtract(a,axis,dtype,None);
    } // reduce_subtract

    template <typename left_t, typename axis_t>
    constexpr auto reduce_subtract(const left_t& a, const axis_t& axis)
    {
        return reduce_subtract(a,axis,None,None);
    } // reduce_subtract
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP