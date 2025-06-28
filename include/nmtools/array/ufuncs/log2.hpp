#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log2
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log2(t);
        } // operator()
    }; // log2
}

namespace nmtools::view
{
    using log2_t = fun::log2;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log2(const left_t& a)
    {
        return unary_ufunc(log2_t{},a);
    } // log2
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log2,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log2) const
        {
            nmtools_string str;

            str += "log2";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG2_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/log2.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log2 = fun::unary_ufunc<view::log2_t>;
    }

    constexpr inline auto log2 = functor_t{unary_fmap_t<fun::log2>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LOG2_HPP
#define NMTOOLS_ARRAY_ARRAY_LOG2_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/log2.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct log2
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto log2 = view::log2(a);
                return eval(log2
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // log2
    } // namespace fn

    constexpr inline auto log2 = fn::log2{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_LOG2_HPP