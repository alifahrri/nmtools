#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct ceil
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::ceil(t);
        } // operator()
    }; // ceil
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using ceil_t = fun::ceil;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto ceil(const left_t& a)
    {
        return unary_ufunc(ceil_t{},a);
    } // ceil
};

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::ceil,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::ceil) const
        {
            nmtools_string str;

            str += "ceil";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CEIL_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/ceil.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using ceil = fun::unary_ufunc<view::ceil_t>;
    }

    constexpr inline auto ceil = functor_t{unary_fmap_t<fun::ceil>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CEIL_HPP
#define NMTOOLS_ARRAY_ARRAY_CEIL_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/ceil.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct ceil
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto ceil = view::ceil(a);
                return eval(ceil
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // ceil
    } // namespace fn

    constexpr inline auto ceil = fn::ceil{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_CEIL_HPP