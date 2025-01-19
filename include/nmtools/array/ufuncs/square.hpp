#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct square
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return t * t;
        } // operator()
    }; // square
}

namespace nmtools::view
{
    using square_t = fun::square;

    template <typename left_t>
    constexpr auto square(const left_t& a)
    {
        return unary_ufunc(square_t{},a);
    } // square
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::square,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::square) const
        {
            nmtools_string str;

            str += "square";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using square = fun::unary_ufunc<view::square_t>;
    }

    constexpr inline auto square = functor_t{unary_fmap_t<fun::square>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SQUARE_HPP
#define NMTOOLS_ARRAY_ARRAY_SQUARE_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct square
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto square = view::square(a);
                return eval(square
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // square
    } // namespace fn

    constexpr inline auto square = fn::square{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SQUARE_HPP