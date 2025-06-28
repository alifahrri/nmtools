#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct reciprocal
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return 1/t;
        } // operator()
    }; // reciprocal
}

namespace nmtools::view
{
    using reciprocal_t = fun::reciprocal;

    template <typename left_t>
    constexpr auto reciprocal(const left_t& a)
    {
        return unary_ufunc(reciprocal_t{},a);
    } // reciprocal
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::reciprocal,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::reciprocal) const
        {
            nmtools_string str;

            str += "reciprocal";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RECIPROCAL_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/reciprocal.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using reciprocal = fun::unary_ufunc<view::reciprocal_t>;
    }

    constexpr inline auto reciprocal = functor_t{unary_fmap_t<fun::reciprocal>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_ARRAY_RECIPROCAL_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/reciprocal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct reciprocal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto reciprocal = view::reciprocal(a);
                return eval(reciprocal
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // reciprocal
    } // namespace fn

    constexpr inline auto reciprocal = fn::reciprocal{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_RECIPROCAL_HPP