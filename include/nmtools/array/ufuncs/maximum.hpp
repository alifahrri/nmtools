#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MAXIMUM_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MAXIMUM_HPP

#include "nmtools/meta.hpp"
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
    struct maximum_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t > u ? t : u;
        } // operator()
    }; // maximum_t

    // TODO: unify with primary template, use static cast ot res_t
    template <typename res_t>
    struct maximum_t<none_t,none_t,res_t
        , meta::enable_if_t<meta::is_num_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t > u ? t : u;
        } // operator()
    }; // maximum_t

    template <typename left_t, typename right_t>
    constexpr auto maximum(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(maximum_t<>{},a,b);
    } // maximum

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto reduce_maximum(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = maximum_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // reduce_maximum

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto reduce_maximum(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = maximum_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial);
    } // reduce_maximum

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto reduce_maximum(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_maximum(a,axis,dtype,None);
    } // reduce_maximum

    // TODO: use default args instead of overload
    template <typename left_t, typename axis_t>
    constexpr auto reduce_maximum(const left_t& a, const axis_t& axis)
    {
        return reduce_maximum(a,axis,None,None);
    } // reduce_maximum

    template <typename left_t, typename axis_t, typename dtype_t>
    auto accumulate_maximum(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = maximum_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_maximum

    template <typename left_t, typename axis_t>
    auto accumulate_maximum(const left_t& a, const axis_t& axis)
    {
        return accumulate_maximum(a,axis,None);
    } // accumulate_maximum

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_maximum(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = maximum_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_maximum
}

#include "nmtools/utility/to_string/to_string.hpp"

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <
        typename lhs_t,
        typename rhs_t,
        typename res_t,
        auto...fmt_args
    >
    struct to_string_t<
        view::maximum_t<lhs_t,rhs_t,res_t>,
        fmt_string_t<fmt_args...>
    >
    {
        using result_type = nmtools_string;

        auto operator()(view::maximum_t<lhs_t,rhs_t,res_t>) const
        {
            auto str = nmtools_string();
            str += "maximum";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MAXIMUM_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufunc/accumulate.hpp"
#include "nmtools/array/ufunc/reduce.hpp"
#include "nmtools/array/ufunc/outer.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using maximum            = fun::broadcast_binary_ufunc<view::maximum_t<>>;
        using reduce_maximum     = fun::reduce<view::maximum_t<>>;
        using outer_maximum      = fun::outer<view::maximum_t<>>;
        using accumulate_maximum = fun::accumulate<view::maximum_t<>>;
    }

    constexpr inline auto maximum = functor_t{binary_fmap_t<fun::maximum>{}};
    constexpr inline auto reduce_maximum = functor_t{unary_fmap_t<fun::reduce_maximum>{}};
    constexpr inline auto outer_maximum = functor_t{binary_fmap_t<fun::outer_maximum>{}};
    constexpr inline auto accumulate_maximum = functor_t{unary_fmap_t<fun::accumulate_maximum>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_MAXIMUM_HPP
#define NMTOOLS_ARRAY_ARRAY_MAXIMUM_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct maximum
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto maximum = view::maximum(a,b);
                return eval(maximum
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
                auto maximum = view::reduce_maximum(a,axis,dtype,initial,keepdims);
                return eval(maximum
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
                auto maximum = view::accumulate_maximum(a,axis,dtype);
                return eval(maximum
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
                auto maximum = view::outer_maximum(a,b,dtype);
                return eval(maximum
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // maximum
    } // namespace fn

    constexpr inline auto maximum = fn::maximum{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MAXIMUM_HPP