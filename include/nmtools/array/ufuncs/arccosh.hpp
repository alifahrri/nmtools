#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arccosh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::acosh(t);
        } // operator()
    }; // arccosh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arccosh_t = fun::arccosh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arccosh(const left_t& a)
    {
        return unary_ufunc(arccosh_t{},a);
    } // arccosh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arccosh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arccosh) const
        {
            nmtools_string str;

            str += "arccosh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOSH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/arccosh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arccosh = fun::unary_ufunc<view::arccosh_t>;
    }

    constexpr inline auto arccosh = functor_t{unary_fmap_t<fun::arccosh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ARCCOSH_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCCOSH_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/arccosh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct arccosh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto arccosh = view::arccosh(a);
                return eval(arccosh
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // arccosh
    } // namespace fn

    constexpr inline auto arccosh = fn::arccosh{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ARCCOSH_HPP