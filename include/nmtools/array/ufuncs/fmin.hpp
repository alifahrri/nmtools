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

    template <typename left_t, typename axis_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type, typename where_t=none_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmin(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}, initial_t init=initial_t{}, keepdims_t keepdims=keepdims_t{}, const where_t& where=where_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmin_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,init,keepdims,where);
    } // reduce_fmin

    template <typename left_t, typename axis_t, typename dtype_t=none_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmin(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmin_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
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

namespace nmtools::array
{
    namespace fn
    {
        struct fmin
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto fmin = view::fmin(a,b);
                return eval(fmin
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
                auto fmin = view::reduce_fmin(a,axis,dtype,initial,keepdims);
                return eval(fmin
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
                auto fmin = view::accumulate_fmin(a,axis,dtype);
                return eval(fmin
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
                auto fmin = view::outer_fmin(a,b,dtype);
                return eval(fmin
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // fmin
    } // namespace fn

    constexpr inline auto fmin = fn::fmin{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FMIN_HPP