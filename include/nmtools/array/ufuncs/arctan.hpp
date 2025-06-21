#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arctan
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::atan(t);
        } // operator()
    }; // arctan
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arctan_t = fun::arctan;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctan(const left_t& a)
    {
        return unary_ufunc(arctan_t{},a);
    } // arctan
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arctan,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arctan) const
        {
            nmtools_string str;

            str += "arctan";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/arctan.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arctan = fun::unary_ufunc<view::arctan_t>;
    }

    constexpr inline auto arctan = functor_t{unary_fmap_t<fun::arctan>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ARCTAN_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCTAN_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/arctan.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct arctan
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto arctan = view::arctan(a);
                return eval(arctan
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // arctan
    } // namespace fn

    constexpr inline auto arctan = fn::arctan{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ARCTAN_HPP