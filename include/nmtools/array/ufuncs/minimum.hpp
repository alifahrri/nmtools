#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP

#include "nmtools/core/ufunc.hpp"
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

    // TODO: unify with primary template, use static cast to res_t
    template <typename res_t>
    struct minimum_t<none_t,none_t,res_t
        , meta::enable_if_t<meta::is_num_v<res_t>>
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
        return broadcast_binary_ufunc(minimum_t<>{},a,b);
    } // minimum

    template <typename left_t, typename axis_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type, typename where_t=none_t>
    constexpr auto reduce_minimum(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{}, const where_t& where=where_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = minimum_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims,where);
    } // reduce_minimum

    template <typename left_t, typename axis_t, typename dtype_t=none_t>
    auto accumulate_minimum(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = minimum_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_minimum

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_minimum(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = minimum_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_minimum
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MINIMUM_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/core/ufunc/accumulate.hpp"
#include "nmtools/core/ufunc/reduce.hpp"
#include "nmtools/core/ufunc/outer.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using minimum            = fun::broadcast_binary_ufunc<view::minimum_t<>>;
        using reduce_minimum     = fun::reduce<view::minimum_t<>>;
        using outer_minimum      = fun::outer<view::minimum_t<>>;
        using accumulate_minimum = fun::accumulate<view::minimum_t<>>;
    }

    constexpr inline auto minimum = functor_t{binary_fmap_t<fun::minimum>{}};
    constexpr inline auto reduce_minimum = functor_t{unary_fmap_t<fun::reduce_minimum>{}};
    constexpr inline auto outer_minimum = functor_t{binary_fmap_t<fun::outer_minimum>{}};
    constexpr inline auto accumulate_minimum = functor_t{unary_fmap_t<fun::accumulate_minimum>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_MINIMUM_HPP
#define NMTOOLS_ARRAY_ARRAY_MINIMUM_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/minimum.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct minimum
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto minimum = view::minimum(a,b);
                return eval(minimum
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
                auto minimum = view::reduce_minimum(a,axis,dtype,initial,keepdims);
                return eval(minimum
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
                auto minimum = view::accumulate_minimum(a,axis,dtype);
                return eval(minimum
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
                auto minimum = view::outer_minimum(a,b,dtype);
                return eval(minimum
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // minimum
    } // namespace fn

    constexpr inline auto minimum = fn::minimum{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MINIMUM_HPP