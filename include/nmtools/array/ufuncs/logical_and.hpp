#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_AND_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_AND_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct logical_and
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return static_cast<bool>(t) && static_cast<bool>(u);
        } // operator()
    }; // logical_and
}

namespace nmtools::view
{
    using logical_and_t = fun::logical_and;

    template <typename left_t, typename right_t>
    constexpr auto logical_and(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(logical_and_t{},a,b);
    } // logical_and

    // TODO: handle dtype, initial, keepdims, where
    template <typename left_t, typename axis_t>
    constexpr auto reduce_logical_and(const left_t& a, const axis_t& axis)
    {
        auto init = true;
        return reduce(logical_and_t{},a,axis,init);
    } // reduce_logical_and
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::logical_and,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::logical_and) const
        {
            auto str = nmtools_string();

            str += "logical_and";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_AND_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LOGICAL_AND_HPP
#define NMTOOLS_ARRAY_ARRAY_LOGICAL_AND_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/logical_and.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct logical_and
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto logical_and = view::logical_and(a,b);
                return eval(logical_and
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // logical_and
    } // namespace fn

    constexpr inline auto logical_and = fn::logical_and{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOGICAL_AND_HPP