#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log1p
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log1p(t);
        } // operator()
    }; // log1p
}

namespace nmtools::view
{
    using log1p_t = fun::log1p;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log1p(const left_t& a)
    {
        return unary_ufunc(log1p_t{},a);
    } // log1p
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log1p,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log1p) const
        {
            nmtools_string str;

            str += "log1p";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG1P_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/log1p.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log1p = fun::unary_ufunc<view::log1p_t>;
    }

    constexpr inline auto log1p = functor_t{unary_fmap_t<fun::log1p>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LOG1P_HPP
#define NMTOOLS_ARRAY_ARRAY_LOG1P_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/log1p.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct log1p
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto log1p = view::log1p(a);
                return eval(log1p
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // log1p
    } // namespace fn

    constexpr inline auto log1p = fn::log1p{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_LOG1P_HPP