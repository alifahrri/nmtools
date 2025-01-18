#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct isinf
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::isinf(t);
        } // operator()
    }; // isinf
}

namespace nmtools::view
{
    using isinf_t = fun::isinf;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto isinf(const left_t& a)
    {
        return unary_ufunc(isinf_t{},a);
    } // isinf
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::isinf,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::isinf) const
        {
            nmtools_string str;

            str += "isinf";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISINF_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/isinf.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using isinf = fun::unary_ufunc<view::isinf_t>;
    }

    constexpr inline auto isinf = functor_t{unary_fmap_t<fun::isinf>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ISINF_HPP
#define NMTOOLS_ARRAY_ARRAY_ISINF_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/isinf.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct isinf
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto isinf = view::isinf(a);
                return eval(isinf
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // isinf
    } // namespace fn

    constexpr inline auto isinf = fn::isinf{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ISINF_HPP