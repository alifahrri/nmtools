#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct trunc
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::trunc(t);
        } // operator()
    }; // trunc
}

namespace nmtools::view
{
    using trunc_t = fun::trunc;

    template <typename left_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto trunc(const left_t& a)
    {
        return unary_ufunc(trunc_t{},a);
    } // trunc
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::trunc,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::trunc) const
        {
            nmtools_string str;

            str += "trunc";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TRUNC_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TRUNC_HPP
#define NMTOOLS_ARRAY_ARRAY_TRUNC_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/trunc.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct trunc
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto trunc = view::trunc(a);
                return eval(trunc
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // trunc
    } // namespace fn

    constexpr inline auto trunc = fn::trunc{};
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_TRUNC_HPP