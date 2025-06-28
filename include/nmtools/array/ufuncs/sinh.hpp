#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct sinh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::sinh(t);
        } // operator()
    }; // sinh
}

namespace nmtools::view
{
    using sinh_t = fun::sinh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sinh(const left_t& a)
    {
        return unary_ufunc(sinh_t{},a);
    } // sinh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::sinh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::sinh) const
        {
            nmtools_string str;

            str += "sinh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SINH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/sinh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using sinh = fun::unary_ufunc<view::sinh_t>;
    }

    constexpr inline auto sinh = functor_t{unary_fmap_t<fun::sinh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SINH_HPP
#define NMTOOLS_ARRAY_ARRAY_SINH_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/sinh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct sinh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto sinh = view::sinh(a);
                return eval(sinh
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // sinh
    } // namespace fn

    constexpr inline auto sinh = fn::sinh{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_SINH_HPP