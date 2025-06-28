#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct subtract
    {
        // NOTE: tried to disable but not successful
        // TODO: remove by unifying with primary template
        #if 0
        // NOTE: required for 'result_type' for reduction
        static constexpr auto result_vtype = [](){
            if constexpr (meta::is_num_v<res_t>) {
                return meta::as_value_v<res_t>;
            } else {
                return meta::as_value_v<none_t>;
            }
        }();
        using result_type = meta::type_t<decltype(result_vtype)>;
        #endif

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            using result_type = res_t;
            if constexpr (is_none_v<result_type>) {
                return t - u;
            } else {
                return static_cast<result_type>(t - u);
            }
        } // operator()
    }; // subtract

    // NOTE: tried to disable but not successful
    // TODO: remove by unifying with primary template
    #if 1
    template <typename res_t>
    struct subtract<none_t,none_t,res_t
        , meta::enable_if_t<meta::is_num_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t - u;
        } // operator()
    }; // subtract
    #endif
}

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t
    >
    using subtract_t = fun::subtract<lhs_t,rhs_t,res_t>;

    template <typename left_t, typename right_t, typename casting_t=casting::auto_t>
    constexpr auto subtract(const left_t& a, const right_t& b, casting_t=casting_t{})
    {
        constexpr auto cast_kind = get_casting_v<casting_t>;
        static_assert( !meta::is_fail_v<decltype(cast_kind)>, "unsupported casting kind" );
        using lhs_t [[maybe_unused]] = meta::get_element_type_t<left_t>;
        using rhs_t [[maybe_unused]] = meta::get_element_type_t<right_t>;
        using casting::Casting;
        if constexpr (cast_kind == Casting::AUTO) {
            return broadcast_binary_ufunc(subtract_t<>{},a,b);
        } else /* if constexpr (cast_kind == Casting::SAME_KIND) */ {
            static_assert( meta::is_same_v<lhs_t,rhs_t>, "unsupported same-kind cast");
            return broadcast_binary_ufunc(subtract_t<lhs_t,rhs_t,rhs_t>{},a,b);
        }
        // TODO: support Casting::EQUIV
    } // subtract

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto reduce_subtract(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_subtract only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_subtract only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = subtract_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // reduce_subtract

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto reduce_subtract(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_subtract only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_subtract only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = subtract_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial);
    } // reduce_subtract

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto reduce_subtract(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_subtract(a,axis,dtype,None);
    } // reduce_subtract

    // TODO: use default args instead of overloads!
    template <typename left_t, typename axis_t>
    constexpr auto reduce_subtract(const left_t& a, const axis_t& axis)
    {
        return reduce_subtract(a,axis,None,None);
    } // reduce_subtract

    template <typename left_t, typename axis_t, typename dtype_t>
    auto accumulate_subtract(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = subtract_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_subtract

    template <typename left_t, typename axis_t>
    auto accumulate_subtract(const left_t& a, const axis_t& axis)
    {
        return accumulate_subtract(a,axis,None);
    } // accumulate_subtract

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_subtract(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = subtract_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_subtract
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <
        typename lhs_t,
        typename rhs_t,
        typename res_t,
        auto...fmt_args
    >
    struct to_string_t<view::fun::subtract<lhs_t,rhs_t,res_t>,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::subtract<lhs_t,rhs_t,res_t>) const
        {
            auto str = nmtools_string();

            str += "subtract";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SUBTRACT_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/core/ufunc/accumulate.hpp"
#include "nmtools/core/ufunc/reduce.hpp"
#include "nmtools/core/ufunc/outer.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using subtract            = fun::broadcast_binary_ufunc<view::subtract_t<>>;
        using reduce_subtract     = fun::reduce<view::subtract_t<>>;
        using outer_subtract      = fun::outer<view::subtract_t<>>;
        using accumulate_subtract = fun::accumulate<view::subtract_t<>>;
    }

    constexpr inline auto subtract = functor_t{binary_fmap_t<fun::subtract>{}};
    constexpr inline auto reduce_subtract = functor_t{unary_fmap_t<fun::reduce_subtract>{}};
    constexpr inline auto outer_subtract = functor_t{binary_fmap_t<fun::outer_subtract>{}};
    constexpr inline auto accumulate_subtract = functor_t{unary_fmap_t<fun::accumulate_subtract>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SUBTRACT_HPP
#define NMTOOLS_ARRAY_ARRAY_SUBTRACT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct subtract
        {
            // TODO: create specific traits for context and output to differentiate eval args and view args
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto subtract = view::subtract(a,b);
                return eval(subtract
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b, casting::same_kind_t,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto subtract = view::subtract(a,b,casting::same_kind_t{});
                return eval(subtract
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
                auto subtract = view::reduce_subtract(a,axis,dtype,initial,keepdims);
                return eval(subtract
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
                auto subtract = view::accumulate_subtract(a,axis,dtype);
                return eval(subtract
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
                auto subtract = view::outer_subtract(a,b,dtype);
                return eval(subtract
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // subtract
    } // namespace fn

    constexpr inline auto subtract = fn::subtract{};
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_SUBTRACT_HPP