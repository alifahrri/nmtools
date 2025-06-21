#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct sin
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sin(t);
        } // operator()
    }; // sin
}

namespace nmtools::view
{
    using sin_t = fun::sin;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sin(const left_t& a)
    {
        return unary_ufunc(sin_t{},a);
    } // sin
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::sin,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::sin) const
        {
            nmtools_string str;

            str += "sin";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SIN_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/sin.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using sin = fun::unary_ufunc<view::sin_t>;
    }

    constexpr inline auto sin = functor_t{unary_fmap_t<fun::sin>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SIN_HPP
#define NMTOOLS_ARRAY_ARRAY_SIN_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/sin.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct sin
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto sin = view::sin(a);
                return eval(sin
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // sin
    } // namespace fn

    constexpr inline auto sin = fn::sin{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_SIN_HPP