#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct negative
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return -t;
        } // operator()
    }; // negative
}

namespace nmtools::view
{
    using negative_t = fun::negative;

    template <typename left_t>
    constexpr auto negative(const left_t& a)
    {
        return unary_ufunc(negative_t{},a);
    } // negative
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::negative,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::negative) const
        {
            nmtools_string str;

            str += "negative";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_NEGATIVE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/negative.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using negative = fun::unary_ufunc<view::negative_t>;
    }

    constexpr inline auto negative = functor_t{unary_fmap_t<fun::negative>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_NEGATIVE_HPP
#define NMTOOLS_ARRAY_ARRAY_NEGATIVE_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/negative.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct negative
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto negative = view::negative(a);
                return eval(negative
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // negative
    } // namespace fn

    constexpr inline auto negative = fn::negative{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_NEGATIVE_HPP