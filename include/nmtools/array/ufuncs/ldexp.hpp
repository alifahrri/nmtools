#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct ldexp
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::ldexp(t,u);
        } // operator()
    }; // ldexp
}
namespace nmtools::view
{
    using ldexp_t = fun::ldexp;

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto ldexp(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(ldexp_t{},a,b);
    } // ldexp
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::ldexp,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::ldexp) const
        {
            auto str = nmtools_string();

            str += "ldexp";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LDEXP_HPP
#define NMTOOLS_ARRAY_ARRAY_LDEXP_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/ldexp.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct ldexp
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto ldexp = view::ldexp(a,b);
                return eval(ldexp
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // ldexp
    } // namespace fn

    constexpr inline auto ldexp = fn::ldexp{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_LDEXP_HPP