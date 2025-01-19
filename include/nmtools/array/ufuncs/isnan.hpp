#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct isnan
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::isnan(t);
        } // operator()
    }; // isnan
}

namespace nmtools::view
{
    using isnan_t = fun::isnan;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto isnan(const left_t& a)
    {
        return unary_ufunc(isnan_t{},a);
    } // isnan
};

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::isnan,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::isnan) const
        {
            nmtools_string str;

            str += "isnan";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ISNAN_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/isnan.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using isnan = fun::unary_ufunc<view::isnan_t>;
    }

    constexpr inline auto isnan = functor_t{unary_fmap_t<fun::isnan>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ISNAN_HPP
#define NMTOOLS_ARRAY_ARRAY_ISNAN_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/isnan.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct isnan
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto isnan = view::isnan(a);
                return eval(isnan
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // isnan
    } // namespace fn

    constexpr inline auto isnan = fn::isnan{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ISNAN_HPP