#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct less_equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t <= u;
        } // operator()
    }; // less_equal
}

namespace nmtools::view
{
    using less_equal_t = fun::less_equal;

    template <typename left_t, typename right_t>
    constexpr auto less_equal(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(less_equal_t{},a,b);
    } // less_equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::less_equal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::less_equal) const
        {
            auto str = nmtools_string();

            str += "less_equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LESS_EQUAL_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LESS_EQUAL_HPP
#define NMTOOLS_ARRAY_ARRAY_LESS_EQUAL_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/less_equal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct less_equal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto less_equal = view::less_equal(a,b);
                return eval(less_equal
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // less_equal
    } // namespace fn

    constexpr inline auto less_equal = fn::less_equal{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LESS_EQUAL_HPP