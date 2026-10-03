#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMIN_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct fmin_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::fmin(t,u);
        } // operator()
    }; // fmin_t

    // TODO: unify with primary template, use static cast to rhs_t
    template <typename rhs_t>
    struct fmin_t<none_t,none_t,rhs_t,
        meta::enable_if_t<meta::is_num_v<rhs_t>>
    >
    {
        using result_type = rhs_t;

        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const -> rhs_t
        {
            return math::fmin(t,u);
        } // operator()
    }; // fmin_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmin(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(fmin_t<>{},a,b);
    } // fmin

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmin(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t init, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmin_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,init,keepdims);
    } // reduce_fmin

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmin(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t init)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmin_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,init);
    } // reduce_fmin

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmin(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return view::reduce_fmin(a,axis,dtype,None);
    } // reduce_fmin

    // TODO: use default args, instead of overloads
    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmin(const left_t& a, const axis_t& axis)
    {
        return view::reduce_fmin(a,axis,None,None);
    } // reduce_fmin

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmin(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmin_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_fmin

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmin(const left_t& a, const axis_t& axis)
    {
        return view::accumulate_fmin(a,axis,None);
    } // accumulate_fmin

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto outer_fmin(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmin_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_fmin
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMIN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FMIN_HPP
#define NMTOOLS_ARRAY_ARRAY_FMIN_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/fmin.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=default_context_t<>,
        typename left_t, typename right_t>
    constexpr inline auto fmin(const left_t& a, const right_t& b,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto fmin = view::fmin(a,b);
        return eval(fmin
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // fmin

    template <typename output_t=none_t, typename context_t=default_context_t<>,
        typename left_t, typename right_t>
    constexpr inline auto fmin(const left_t& a, const right_t& b, casting::same_kind_t,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto fmin = view::fmin(a,b,casting::same_kind_t{});
        return eval(fmin
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // fmin

    template <typename output_t=none_t
        , typename context_t=default_context_t<>
        , typename dtype_t=none_t
        , typename initial_t=none_t
        , typename keepdims_t=meta::false_type
        , typename left_t
        , typename axis_t
        , enable_if_t<is_none_v<dtype_t> || is_dtype_v<dtype_t>,int> = 0
        , enable_if_t<is_none_v<initial_t> || is_num_v<initial_t>,int> = 0
        , enable_if_t<is_none_v<keepdims_t> || is_num_v<keepdims_t>,int> = 0>
    constexpr auto reduce_fmin(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}
        , initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto fmin = view::reduce_fmin(a,axis,dtype,initial,keepdims);
        return eval(fmin
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
        );
    } // reduce

    template <typename context_t
        , typename left_t
        , typename axis_t
        , typename dtype_t
        , typename initial_t
        , enable_if_t<is_none_v<dtype_t> || is_dtype_v<dtype_t>,int> = 0
        , enable_if_t<is_none_v<initial_t> || is_num_v<initial_t>,int> = 0
        , enable_if_t<is_context_v<context_t> || is_context_ptr_v<context_t>,int> = 0>
    constexpr auto reduce_fmin(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial
        , context_t&& context)
    {
        auto fmin = view::reduce_fmin(a,axis,dtype,initial);
        return eval(fmin
            , nmtools::forward<context_t>(context)
        );
    } // reduce

    template <typename context_t
        , typename left_t
        , typename axis_t
        , typename dtype_t
        , enable_if_t<is_none_v<dtype_t> || is_dtype_v<dtype_t>,int> = 0
        , enable_if_t<is_context_v<context_t> || is_context_ptr_v<context_t>,int> = 0>
    constexpr auto reduce_fmin(const left_t& a, const axis_t& axis, dtype_t dtype
        , context_t&& context)
    {
        auto fmin = view::reduce_fmin(a,axis,dtype);
        return eval(fmin
            , nmtools::forward<context_t>(context)
        );
    } // reduce

    template <typename context_t
        , typename left_t
        , typename axis_t
        , enable_if_t<is_context_v<context_t> || is_context_ptr_v<context_t>,int> = 0>
    constexpr auto reduce_fmin(const left_t& a, const axis_t& axis
        , context_t&& context)
    {
        auto fmin = view::reduce_fmin(a,axis);
        return eval(fmin
            , nmtools::forward<context_t>(context)
        );
    } // reduce

    template <typename output_t=none_t
        , typename context_t=default_context_t<>
        , typename dtype_t=none_t
        , typename left_t
        , typename axis_t
        , enable_if_t<is_none_v<dtype_t> || is_dtype_v<dtype_t>,int> = 0>
    constexpr auto accumulate_fmin(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto fmin = view::accumulate_fmin(a,axis,dtype);
        return eval(fmin
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // accumulate_fmin

    template <typename context_t
        , typename left_t
        , typename axis_t
        , enable_if_t<is_context_v<context_t> || is_context_ptr_v<context_t>,int> = 0>
    constexpr auto accumulate_fmin(const left_t& a, const axis_t& axis
        , context_t&& context)
    {
        auto fmin = view::accumulate_fmin(a,axis);
        return eval(fmin
            , nmtools::forward<context_t>(context)
        );
    } // accumulate_fmin

    template <typename output_t=none_t
        , typename context_t=default_context_t<>
        , typename dtype_t=none_t
        , typename left_t
        , typename right_t
        , enable_if_t<is_none_v<dtype_t> || is_dtype_v<dtype_t>,int> = 0>
    constexpr auto outer_fmin(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto fmin = view::outer_fmin(a,b,dtype);
        return eval(fmin
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // outer_fmin

    template <typename context_t
        , typename left_t
        , typename right_t
        , enable_if_t<is_context_v<context_t> || is_context_ptr_v<context_t>,int> = 0>
    constexpr auto outer_fmin(const left_t& a, const right_t& b
        , context_t&& context)
    {
        auto fmin = view::outer_fmin(a,b);
        return eval(fmin
            , nmtools::forward<context_t>(context)
        );
    } // outer_fmin
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_FMIN_HPP