#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct exp
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::exp(t);
        } // operator()
    }; // exp
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using exp_t = fun::exp;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto exp(const left_t& a)
    {
        return unary_ufunc(exp_t{},a);
    } // exp
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::exp,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::exp) const
        {
            nmtools_string str;

            str += "exp";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXP_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using exp = fun::unary_ufunc<view::exp_t>;
    }

    constexpr inline auto exp = functor_t{unary_fmap_t<fun::exp>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_EXP_HPP
#define NMTOOLS_ARRAY_ARRAY_EXP_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct exp
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto exp = view::exp(a);
                return eval(exp
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // exp
    } // namespace fn

    constexpr inline auto exp = fn::exp{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EXP_HPP