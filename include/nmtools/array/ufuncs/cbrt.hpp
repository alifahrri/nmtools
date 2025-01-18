#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct cbrt
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::cbrt(t);
        } // operator()
    }; // cbrt
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using cbrt_t = fun::cbrt;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto cbrt(const left_t& a)
    {
        return unary_ufunc(cbrt_t{},a);
    } // cbrt
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::cbrt,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::cbrt) const
        {
            nmtools_string str;

            str += "cbrt";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CBRT_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/cbrt.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using cbrt = fun::unary_ufunc<view::cbrt_t>;
    }

    constexpr inline auto cbrt = functor_t{unary_fmap_t<fun::cbrt>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CBRT_HPP
#define NMTOOLS_ARRAY_ARRAY_CBRT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/cbrt.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct cbrt
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto cbrt = view::cbrt(a);
                return eval(cbrt
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // cbrt
    } // namespace fn

    constexpr inline auto cbrt = fn::cbrt{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CBRT_HPP