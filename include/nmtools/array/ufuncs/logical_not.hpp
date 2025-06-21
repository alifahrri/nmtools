#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct logical_not
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return !static_cast<bool>(t);
        } // operator()
    }; // logical_not
}

namespace nmtools::view
{
    using logical_not_t = fun::logical_not;

    template <typename left_t>
    constexpr auto logical_not(const left_t& a)
    {
        return unary_ufunc(logical_not_t{},a);
    } // logical_not
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::logical_not,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::logical_not) const
        {
            auto str = nmtools_string();

            str += "logical_not";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING


#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_NOT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LOGICAL_NOT_HPP
#define NMTOOLS_ARRAY_ARRAY_LOGICAL_NOT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/logical_not.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct logical_not
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto logical_not = view::logical_not(a);
                return eval(logical_not
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // logical_not
    } // namespace fn

    constexpr inline auto logical_not = fn::logical_not{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_LOGICAL_NOT_HPP