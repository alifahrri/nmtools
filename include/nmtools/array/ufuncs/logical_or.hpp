#ifndef NMTOOLS_ARRAY_UFUNCS_LOGICAL_OR_HPP
#define NMTOOLS_ARRAY_UFUNCS_LOGICAL_OR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct logical_or
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return static_cast<bool>(t) || static_cast<bool>(u);
        } // operator()
    }; // logical_or
}

namespace nmtools::view
{
    using logical_or_t = fun::logical_or;

    template <typename left_t, typename right_t>
    constexpr auto logical_or(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(logical_or_t{},a,b);
    } // logical_or

    template <typename left_t
        , typename axis_t
        , typename dtype_t=none_t
        , typename initial_t=none_t
        , typename keepdims_t=meta::false_type
        , typename where_t=none_t>
    constexpr auto reduce_logical_or(const left_t& a, const axis_t& axis
        , dtype_t dtype=dtype_t{}
        , initial_t initial=initial_t{}
        , keepdims_t keepdims=keepdims_t{}
        , const where_t& where=where_t{})
    {
        return reduce(logical_or_t{},a,axis,dtype,initial,keepdims,where);
    } // reduce_logical_or
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::logical_or,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::logical_or) const
        {
            auto str = nmtools_string();

            str += "logical_or";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#include "nmtools/core/eval.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct logical_or
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto logical_or = view::logical_or(a,b);
                return eval(logical_or
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                );
            } // operator()
        }; // logical_or
    } // namespace fn

    constexpr inline auto logical_or = fn::logical_or{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_UFUNCS_LOGICAL_OR_HPP