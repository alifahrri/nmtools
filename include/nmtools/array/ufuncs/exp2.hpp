#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct exp2
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::exp2(t);
        } // operator()
    }; // exp2
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using exp2_t = fun::exp2;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto exp2(const left_t& a)
    {
        return unary_ufunc(exp2_t{},a);
    } // exp2
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::exp2,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::exp2) const
        {
            nmtools_string str;

            str += "exp2";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_EXP2_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/exp2.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using exp2 = fun::unary_ufunc<view::exp2_t>;
    }

    constexpr inline auto exp2 = functor_t{unary_fmap_t<fun::exp2>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_EXP2_HPP
#define NMTOOLS_ARRAY_ARRAY_EXP2_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/exp2.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct exp2
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto exp2 = view::exp2(a);
                return eval(exp2
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // exp2
    } // namespace fn

    constexpr inline auto exp2 = fn::exp2{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EXP2_HPP