#ifndef NMTOOLS_ARRAY_UFUNCS_MAXIMUM_HPP
#define NMTOOLS_ARRAY_UFUNCS_MAXIMUM_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/ufunc/accumulate.hpp"
#include "nmtools/core/ufunc/reduce.hpp"
#include "nmtools/core/ufunc/outer.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::view::fun
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct maximum
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            using result_type = res_t;
            if constexpr (is_none_v<result_type>) {
                return t > u ? t : u;
            } else {
                // Assume T and U can be compared, result cast to result_type
                return static_cast<result_type>(t > u ? t : u);
            }
        }
    };

    // TODO: unify with primary template, use static cast ot res_t
    template <typename res_t>
    struct maximum<none_t,none_t,res_t
        , meta::enable_if_t<meta::is_num_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t > u ? t : u;
        }
    };
} // namespace nmtools::view::fun

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t
    >
    using maximum_t = fun::maximum<lhs_t,rhs_t,res_t>;

    template <typename left_t, typename right_t, typename casting_t=casting::auto_t>
    constexpr auto maximum(const left_t& a, const right_t& b, casting_t=casting_t{})
    {
        constexpr auto cast_kind = get_casting_v<casting_t>;
        static_assert( !meta::is_fail_v<decltype(cast_kind)>, "unsupported casting kind" );
        using lhs_t [[maybe_unused]] = meta::get_element_type_t<left_t>;
        using rhs_t [[maybe_unused]] = meta::get_element_type_t<right_t>;
        using casting::Casting;
        if constexpr (cast_kind == Casting::AUTO) {
            return broadcast_binary_ufunc(maximum_t<>{},a,b);
        } else /* if constexpr (cast_kind == Casting::SAME_KIND) */ {
            static_assert( meta::is_same_v<lhs_t,rhs_t>, "unsupported same-kind cast");
            return broadcast_binary_ufunc(maximum_t<lhs_t,rhs_t,rhs_t>{},a,b);
        }
        // TODO: support Casting::EQUIV
    }

    template <typename left_t, typename axis_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type, typename where_t=none_t>
    constexpr auto reduce_maximum(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{}, const where_t& where=where_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = maximum_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims,where);
    }

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t, typename op_t=none_t>
    constexpr auto reduce_maximum(const left_t& a, const args::reduce<axis_t,dtype_t,initial_t,keepdims_t,op_t>& attributes)
    {
        return reduce_maximum(a
            , attributes.axis
            , attributes.dtype
            , attributes.initial
            , attributes.keepdims
        );
    }

    template <typename left_t, typename axis_t, typename dtype_t=none_t>
    constexpr auto accumulate_maximum(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = maximum_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    }

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_maximum(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = maximum_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    }

} // namespace nmtools::view

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
        view::fun::maximum<lhs_t,rhs_t,res_t>, // Corrected from view::maximum_t
        fmt_string_t<fmt_args...>
    >
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::maximum<lhs_t,rhs_t,res_t>) const // Corrected from view::maximum_t
        {
            auto str = nmtools_string();
            str += "maximum";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

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


namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename dtype_t=none_t, typename initial_t=none_t
        , typename keepdims_t=meta::false_type, typename where_t=none_t
        , typename left_t, typename axis_t>
    constexpr auto reduce_maximum(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}
        , initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{}, const where_t& where=where_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto maximum_view = view::reduce_maximum(a,axis,dtype,initial,keepdims,where);
        return eval(maximum_view
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename dtype_t=none_t, typename left_t, typename axis_t>
    constexpr auto accumulate_maximum(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto maximum_view = view::accumulate_maximum(a,axis,dtype);
        return eval(maximum_view
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename dtype_t=none_t, typename left_t, typename right_t>
    constexpr auto outer_maximum(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto maximum_view = view::outer_maximum(a,b,dtype);
        return eval(maximum_view
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }

    namespace fn
    {
        struct maximum
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
                , typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b
                , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto maximum_view = view::maximum(a,b);
                return eval(maximum_view
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                );
            }

             template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
                , typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b, casting::same_kind_t casting_type
                , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto maximum_view = view::maximum(a,b,casting_type);
                return eval(maximum_view
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                );
            }

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
                , typename dtype_t=none_t, typename initial_t=none_t
                , typename keepdims_t=meta::false_type, typename where_t=none_t,
                typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}
                , initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{}, const where_t& where=where_t{}
                , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                return array::reduce_maximum(a,axis,dtype,initial,keepdims,where
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                );
            }

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
                , typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}
                , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                return array::accumulate_maximum(a,axis,dtype
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                );
            }

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
                , typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{}
                , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                return array::outer_maximum(a,b,dtype
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                );
            }
        };
    }

    constexpr inline auto maximum = fn::maximum{};

} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_UFUNCS_MAXIMUM_HPP