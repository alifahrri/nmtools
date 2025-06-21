#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct hypot
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::hypot(t,u);
        } // operator()
    }; // hypot
}

namespace nmtools::view
{
    using hypot_t = fun::hypot;

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto hypot(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(hypot_t{},a,b);
    } // hypot
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::hypot,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::hypot) const
        {
            auto str = nmtools_string();

            str += "hypot";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_HYPOT_HPP
#define NMTOOLS_ARRAY_ARRAY_HYPOT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/hypot.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct hypot
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b, context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto hypot = view::hypot(a,b);
                return eval(hypot, nmtools::forward<context_t>(context), nmtools::forward<output_t>(output), resolver);
            } // operator()
        }; // hypot
    } // namespace fn

    constexpr inline auto hypot = fn::hypot{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_HYPOT_HPP