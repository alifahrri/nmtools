#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP

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
    struct fmax_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::fmax(t,u);
        } // operator()
    }; // fmax_t

    // TODO: unify with primary template, use static cast to rhs_t
    template <typename rhs_t>
    struct fmax_t<none_t,none_t,rhs_t,
        meta::enable_if_t<meta::is_num_v<rhs_t>>
    >
    {
        using result_type = rhs_t;

        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const -> rhs_t
        {
            return math::fmax(t,u);
        } // operator()
    }; // fmax_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmax(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(fmax_t<>{},a,b);
    } // fmax

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmax(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t init, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmax_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,init,keepdims);
    } // reduce_fmax

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmax(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t init)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmax_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,init);
    } // reduce_fmax

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmax(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_fmax(a,axis,dtype,None);
    } // reduce_fmax

    // TODO: use default args instead of overload
    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmax(const left_t& a, const axis_t& axis)
    {
        return reduce_fmax(a,axis,None,None);
    } // reduce_fmax

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmax(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmax_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_fmax

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmax(const left_t& a, const axis_t& axis)
    {
        return accumulate_fmax(a,axis,None);
    } // accumulate_fmax

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto outer_fmax(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmax_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_fmax
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMAX_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FMAX_HPP
#define NMTOOLS_ARRAY_ARRAY_FMAX_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/fmax.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct fmax
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto fmax = view::fmax(a,b);
                return eval(fmax
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=meta::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto fmax = view::reduce_fmax(a,axis,dtype,initial,keepdims);
                return eval(fmax
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto fmax = view::accumulate_fmax(a,axis,dtype);
                return eval(fmax
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto fmax = view::outer_fmax(a,b,dtype);
                return eval(fmax
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // fmax
    } // namespace fn

    constexpr inline auto fmax = fn::fmax{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FMAX_HPP