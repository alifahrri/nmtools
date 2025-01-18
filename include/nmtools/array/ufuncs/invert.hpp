#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::meta::error
{
    template <typename...>
    struct INVERT_UNSUPPORTED : detail::fail_t {};
}

namespace nmtools::view::fun
{
    struct invert
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            if constexpr (meta::expression_check_v<meta::expr::invert,T>) {
                return ~t;
            } else {
                return meta::error::INVERT_UNSUPPORTED<T>{};
            }
        } // operator()
    }; // invert   
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using invert_t = fun::invert;
    template <typename left_t>
    constexpr auto invert(const left_t& a)
    {
        return unary_ufunc(invert_t{},a);
    } // invert
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::invert,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::invert) const
        {
            nmtools_string str;

            str += "invert";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/invert.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using invert = fun::unary_ufunc<view::invert_t>;
    }

    constexpr inline auto invert = functor_t{unary_fmap_t<fun::invert>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_INVERT_HPP
#define NMTOOLS_ARRAY_ARRAY_INVERT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/invert.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct invert
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto invert = view::invert(a);
                return eval(invert
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // invert
    } // namespace fn

    constexpr inline auto invert = fn::invert{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_INVERT_HPP