#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct cosh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::cosh(t);
        } // operator()
    }; // cosh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using cosh_t = fun::cosh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto cosh(const left_t& a)
    {
        return unary_ufunc(cosh_t{},a);
    } // cosh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::cosh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::cosh) const
        {
            nmtools_string str;

            str += "cosh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_COSH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/cosh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using cosh = fun::unary_ufunc<view::cosh_t>;
    }

    constexpr inline auto cosh = functor_t{unary_fmap_t<fun::cosh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_COSH_HPP
#define NMTOOLS_ARRAY_ARRAY_COSH_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/cosh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct cosh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto cosh = view::cosh(a);
                return eval(cosh
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // cosh
    } // namespace fn

    constexpr inline auto cosh = fn::cosh{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_COSH_HPP