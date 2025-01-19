#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_NOT_EQUAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_NOT_EQUAL_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct not_equal
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t != u;
        } // operator()
    }; // not_equal
}

namespace nmtools::view
{
    using not_equal_t = fun::not_equal;

    template <typename left_t, typename right_t>
    constexpr auto not_equal(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(not_equal_t{},a,b);
    } // not_equal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::not_equal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::not_equal) const
        {
            auto str = nmtools_string();

            str += "not_equal";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_NOT_EQUAL_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_NOT_EQUAL_HPP
#define NMTOOLS_ARRAY_ARRAY_NOT_EQUAL_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/not_equal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct not_equal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto not_equal = view::not_equal(a,b);
                return eval(not_equal
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // not_equal
    } // namespace fn

    constexpr inline auto not_equal = fn::not_equal{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_NOT_EQUAL_HPP