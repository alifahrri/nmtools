#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP

#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct greater_equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t >= u;
        } // operator()
    }; // greater_equal
}

namespace nmtools::view
{
    using greater_equal_t = fun::greater_equal;

    template <typename left_t, typename right_t>
    constexpr auto greater_equal(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(greater_equal_t{},a,b);
    } // greater_equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::greater_equal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::greater_equal) const
        {
            auto str = nmtools_string();

            str += "greater_equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_EQUAL_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_GREATER_EQUAL_HPP
#define NMTOOLS_ARRAY_ARRAY_GREATER_EQUAL_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct greater_equal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto greater_equal = view::greater_equal(a,b);
                return eval(greater_equal
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // greater_equal
    } // namespace fn

    constexpr inline auto greater_equal = fn::greater_equal{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_GREATER_EQUAL_HPP