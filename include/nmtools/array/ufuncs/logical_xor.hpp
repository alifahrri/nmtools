#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct logical_xor
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return static_cast<bool>(t) ^ static_cast<bool>(u);
        } // operator()
    }; // logical_xor
}

namespace nmtools::view
{
    using logical_xor_t = fun::logical_xor;

    template <typename left_t, typename right_t>
    constexpr auto logical_xor(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(logical_xor_t{},a,b);
    } // logical_xor

    template <typename left_t, typename axis_t>
    constexpr auto reduce_logical_xor(const left_t& a, const axis_t& axis)
    {
        auto init = false;
        return reduce(logical_xor_t{},a,axis,init);
    } // reduce_logical_xor
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::logical_xor,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::logical_xor) const
        {
            auto str = nmtools_string();

            str += "logical_xor";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LOGICAL_XOR_HPP
#define NMTOOLS_ARRAY_ARRAY_LOGICAL_XOR_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/logical_xor.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct logical_xor
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto logical_xor = view::logical_xor(a,b);
                return eval(logical_xor
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // logical_xor
    } // namespace fn

    constexpr inline auto logical_xor = fn::logical_xor{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOGICAL_XOR_HPP