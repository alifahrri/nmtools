#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct rint
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::rint(t);
        } // operator()
    }; // rint
}

namespace nmtools::view
{
    using rint_t = fun::rint;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto rint(const left_t& a)
    {
        return unary_ufunc(rint_t{},a);
    } // rint
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::rint,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::rint) const
        {
            nmtools_string str;

            str += "rint";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RINT_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/rint.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using rint = fun::unary_ufunc<view::rint_t>;
    }

    constexpr inline auto rint = functor_t{unary_fmap_t<fun::rint>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_RINT_HPP
#define NMTOOLS_ARRAY_ARRAY_RINT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/rint.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct rint
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto rint = view::rint(a);
                return eval(rint
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // rint
    } // namespace fn

    constexpr inline auto rint = fn::rint{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RINT_HPP