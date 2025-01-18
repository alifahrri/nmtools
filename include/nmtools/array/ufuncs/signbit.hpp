#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct signbit
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::signbit(t);
        } // operator()
    }; // signbit
}

namespace nmtools::view
{
    using signbit_t = fun::signbit;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto signbit(const left_t& a)
    {
        return unary_ufunc(signbit_t{},a);
    } // signbit
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::signbit,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::signbit) const
        {
            nmtools_string str;

            str += "signbit";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SIGNBIT_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/signbit.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using signbit = fun::unary_ufunc<view::signbit_t>;
    }

    constexpr inline auto signbit = functor_t{unary_fmap_t<fun::signbit>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SIGNBIT_HPP
#define NMTOOLS_ARRAY_ARRAY_SIGNBIT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/signbit.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct signbit
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto signbit = view::signbit(a);
                return eval(signbit
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // signbit
    } // namespace fn

    constexpr inline auto signbit = fn::signbit{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SIGNBIT_HPP