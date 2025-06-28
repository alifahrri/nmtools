#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct expm1
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::expm1(t);
        } // operator()
    }; // expm1
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using expm1_t = fun::expm1;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto expm1(const left_t& a)
    {
        return unary_ufunc(expm1_t{},a);
    } // expm1
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::expm1,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::expm1) const
        {
            nmtools_string str;

            str += "expm1";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXPM1_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/expm1.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using expm1 = fun::unary_ufunc<view::expm1_t>;
    }

    constexpr inline auto expm1 = functor_t{unary_fmap_t<fun::expm1>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_EXPM1_HPP
#define NMTOOLS_ARRAY_ARRAY_EXPM1_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/expm1.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct expm1
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>, typename left_t>
            inline constexpr auto operator()(const left_t& a, context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto expm1 = view::expm1(a);
                return eval(expm1, nmtools::forward<context_t>(context), nmtools::forward<output_t>(output), resolver);
            } // operator()
        }; // expm1
    } // namespace fn

    constexpr inline auto expm1 = fn::expm1{};
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_EXPM1_HPP