#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/constants.hpp"

#include <cmath>

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct fmod_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return std::fmod(t,u);
        } // operator()
    }; // fmod_t

    template <typename res_t>
    struct fmod_t<none_t,none_t,res_t,std::enable_if_t<std::is_arithmetic_v<res_t>>>
    {
        using result_type = res_t;

        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const -> res_t
        {
            return std::fmod(t,u);
        } // operator()
    }; // fmod_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmod(const left_t& a, const right_t& b)
    {
        return ufunc(fmod_t<>{},a,b);
    } // fmod

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        static_assert( std::is_integral_v<axis_t>
            , "reduce_fmod only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_fmod only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmod_t<none_t,none_t,res_t>; 
        return reduce(op_t{},a,axis,initial,keepdims);
    } // reduce_fmod

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        static_assert( std::is_integral_v<axis_t>
            , "reduce_fmod only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_fmod only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmod_t<none_t,none_t,res_t>; 
        return reduce(op_t{},a,axis,initial);
    } // reduce_fmod

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_fmod(a,axis,dtype,None);
    } // reduce_fmod

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis)
    {
        return reduce_fmod(a,axis,None,None);
    } // reduce_fmod

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmod(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmod_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis);
    } // accumulate_fmod

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmod(const left_t& a, const axis_t& axis)
    {
        return accumulate_fmod(a,axis,None);
    } // accumulate_fmod
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP