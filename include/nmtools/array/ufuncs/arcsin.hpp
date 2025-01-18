#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arcsin
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::asin(t);
        } // operator()
    }; // arcsin
} // nmtools::view::fun

namespace nmtools::view
{
    using arcsin_t = fun::arcsin;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arcsin(const left_t& a)
    {
        return unary_ufunc(arcsin_t{},a);
    } // arcsin
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arcsin,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arcsin) const
        {
            nmtools_string str;

            str += "arcsin";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSIN_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/arcsin.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arcsin = fun::unary_ufunc<view::arcsin_t>;
    }

    constexpr inline auto arcsin = functor_t{unary_fmap_t<fun::arcsin>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ARCSIN_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCSIN_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/arcsin.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct arcsin
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto arcsin = view::arcsin(a);
                return eval(arcsin
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // arcsin
    } // namespace fn

    constexpr inline auto arcsin = fn::arcsin{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ARCSIN_HPP