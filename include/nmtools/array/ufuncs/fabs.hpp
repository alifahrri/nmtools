#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct fabs
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::fabs(t);
        } // operator()
    }; // fabs
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using fabs_t = fun::fabs;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto fabs(const left_t& a)
    {
        return unary_ufunc(fabs_t{},a);
    } // fabs
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::fabs,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::fabs) const
        {
            nmtools_string str;

            str += "fabs";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FABS_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using fabs = fun::unary_ufunc<view::fabs_t>;
    }

    constexpr inline auto fabs = functor_t{unary_fmap_t<fun::fabs>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FABS_HPP
#define NMTOOLS_ARRAY_ARRAY_FABS_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct fabs
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto fabs = view::fabs(a);
                return eval(fabs
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // fabs
    } // namespace fn

    constexpr inline auto fabs = fn::fabs{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FABS_HPP