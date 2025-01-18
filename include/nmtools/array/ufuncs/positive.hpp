#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct positive
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return +t;
        } // operator()
    }; // positive
}

namespace nmtools::view
{
    using positive_t = fun::positive;

    template <typename left_t>
    constexpr auto positive(const left_t& a)
    {
        return unary_ufunc(positive_t{},a);
    } // positive
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::positive,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::positive) const
        {
            nmtools_string str;

            str += "positive";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_POSITIVE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/positive.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using positive = fun::unary_ufunc<view::positive_t>;
    }

    constexpr inline auto positive = functor_t{unary_fmap_t<fun::positive>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP
#define NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/positive.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct positive
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto positive = view::positive(a);
                return eval(positive
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // positive
    } // namespace fn

    constexpr inline auto positive = fn::positive{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP