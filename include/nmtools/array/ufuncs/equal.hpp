#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EQUAL_HPP

#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t == u;
        } // operator()
    }; // equal
}

namespace nmtools::view
{
    using equal_t = fun::equal;

    template <typename left_t, typename right_t>
    constexpr auto equal(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(equal_t{},a,b);
    } // equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::equal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::equal) const
        {
            auto str = nmtools_string();

            str += "equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EQUAL_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_EQUAL_HPP
#define NMTOOLS_ARRAY_ARRAY_EQUAL_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/equal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct equal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b, context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto equal = view::equal(a,b);
                return eval(equal, nmtools::forward<context_t>(context), nmtools::forward<output_t>(output), resolver);
            } // operator()
        }; // equal
    } // namespace fn

    constexpr inline auto equal = fn::equal{};
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_EQUAL_HPP