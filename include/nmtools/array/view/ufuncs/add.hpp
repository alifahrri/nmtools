#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ADD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ADD_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct add_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t + u;
        } // operator()
    }; // add_t

    template <typename res_t>
    struct add_t<none_t,none_t,res_t
        , std::enable_if_t<std::is_arithmetic_v<res_t>> 
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t + u;
        } // operator()
    }; // add_t

    template <typename left_t, typename right_t>
    constexpr auto add(const left_t& a, const right_t& b)
    {
        return ufunc(add_t<>{},a,b);
    } // add

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto reduce_add(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,initial,keepdims);
    } // add

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto reduce_add(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,initial);
    } // add

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto reduce_add(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_add(a,axis,dtype,None);
    } // add

    template <typename left_t, typename axis_t>
    constexpr auto reduce_add(const left_t& a, const axis_t& axis)
    {
        return reduce_add(a,axis,None,None);
    } // add

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto accumulate_add(const left_t& a, axis_t axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis);
    } // accumulate_add

    template <typename left_t, typename axis_t>
    constexpr auto accumulate_add(const left_t& a, axis_t axis)
    {
        return accumulate_add(a,axis,None);
    } // accumulate_add

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_add(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b);
    } // outer_add
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ADD_HPP