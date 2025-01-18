#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct divide
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t / u;
        } // operator()
    }; // divide
}

namespace nmtools::view
{
    using divide_t = fun::divide;

    template <typename left_t, typename right_t>
    constexpr auto divide(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(divide_t{},a,b);
    } // divide
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::divide,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::divide) const
        {
            auto str = nmtools_string();

            str += "divide";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using divide = fun::broadcast_binary_ufunc<view::divide_t>;
    }

    constexpr inline auto divide = functor_t{binary_fmap_t<fun::divide>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_DIVIDE_HPP
#define NMTOOLS_ARRAY_ARRAY_DIVIDE_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct divide
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto divide = view::divide(a,b);
                return eval(divide
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b, casting::same_kind_t,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto divide = view::divide(a,b);
                return eval(divide
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // divide
    } // namespace fn

    constexpr inline auto divide = fn::divide{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_DIVIDE_HPP