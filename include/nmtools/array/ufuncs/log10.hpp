#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log10
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log10(t);
        } // operator()
    }; // log10
}

namespace nmtools::view
{
    using log10_t = fun::log10;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log10(const left_t& a)
    {
        return unary_ufunc(log10_t{},a);
    } // log10
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log10,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log10) const
        {
            nmtools_string str;

            str += "log10";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG10_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/log10.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log10 = fun::unary_ufunc<view::log10_t>;
    }

    constexpr inline auto log10 = functor_t{unary_fmap_t<fun::log10>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LOG10_HPP
#define NMTOOLS_ARRAY_ARRAY_LOG10_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/log10.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct log10
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto log10 = view::log10(a);
                return eval(log10
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // log10
    } // namespace fn

    constexpr inline auto log10 = fn::log10{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOG10_HPP