#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RIGHT_SHIFT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RIGHT_SHIFT_HPP

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
    struct right_shift_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t >> u;
        } // operator()
    }; // right_shift_t

    // TODO: unify with primary template, use static cast to res_t
    template <typename res_t>
    struct right_shift_t<none_t,none_t,res_t,
        meta::enable_if_t<meta::is_num_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t >> u;
        } // operator()
    }; // right_shift_t

    template <typename left_t, typename right_t>
    constexpr auto right_shift(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(right_shift_t<>{},a,b);
    } // right_shift

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto reduce_right_shift(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_right_shift only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_right_shift only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = right_shift_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // reduce_right_shift

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto reduce_right_shift(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_right_shift only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_right_shift only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = right_shift_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial);
    } // reduce_right_shift

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto reduce_right_shift(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_right_shift(a,axis,dtype,None);
    } // reduce_right_shift

    // TODO: use default args instead of overloads!
    template <typename left_t, typename axis_t>
    constexpr auto reduce_right_shift(const left_t& a, const axis_t& axis)
    {
        return reduce_right_shift(a,axis,None,None);
    } // reduce_right_shift

    template <typename left_t, typename axis_t, typename dtype_t>
    auto accumulate_right_shift(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = right_shift_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_right_shift

    template <typename left_t, typename axis_t>
    auto accumulate_right_shift(const left_t& a, const axis_t& axis)
    {
        return accumulate_right_shift(a,axis,None);
    } // accumulate_right_shift

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_right_shift(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = right_shift_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_right_shift
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RIGHT_SHIFT_HPP