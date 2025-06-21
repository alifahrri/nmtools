#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct greater
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            using common_t = meta::common_type_t<T,U>;
            return static_cast<common_t>(t) > static_cast<common_t>(u);
        } // operator()
    }; // greater
}

namespace nmtools::view
{
    using greater_t = fun::greater;

    template <typename left_t, typename right_t>
    constexpr auto greater(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(greater_t{},a,b);
    } // greater
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::greater,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::greater) const
        {
            auto str = nmtools_string();

            str += "greater";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_GREATER_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_GREATER_HPP
#define NMTOOLS_ARRAY_ARRAY_GREATER_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/greater.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct greater
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b, context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto greater = view::greater(a,b);
                return eval(greater, nmtools::forward<context_t>(context), nmtools::forward<output_t>(output), resolver);
            } // operator()
        }; // greater
    } // namespace fn

    constexpr inline auto greater = fn::greater{};
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_GREATER_HPP