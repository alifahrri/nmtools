#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct isfinite
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::isfinite(t);
        } // operator()
    }; // isfinite
}

namespace nmtools::view
{
    using isfinite_t = fun::isfinite;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto isfinite(const left_t& a)
    {
        return unary_ufunc(isfinite_t{},a);
    } // isfinite
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::isfinite,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::isfinite) const
        {
            nmtools_string str;

            str += "isfinite";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISFINITE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/isfinite.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using isfinite = fun::unary_ufunc<view::isfinite_t>;
    }

    constexpr inline auto isfinite = functor_t{unary_fmap_t<fun::isfinite>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ISFINITE_HPP
#define NMTOOLS_ARRAY_ARRAY_ISFINITE_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/isfinite.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct isfinite
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto isfinite = view::isfinite(a);
                return eval(isfinite
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // isfinite
    } // namespace fn

    constexpr inline auto isfinite = fn::isfinite{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ISFINITE_HPP