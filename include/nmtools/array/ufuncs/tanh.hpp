#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct tanh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::tanh(t);
        } // operator()
    }; // tanh
}

namespace nmtools::view
{
    using tanh_t = fun::tanh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tanh(const left_t& a)
    {
        return unary_ufunc(tanh_t{},a);
    } // tanh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::tanh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::tanh) const
        {
            nmtools_string str;

            str += "tanh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TANH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using tanh = fun::unary_ufunc<view::tanh_t>;
    }

    constexpr inline auto tanh = functor_t{unary_fmap_t<fun::tanh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TANH_HPP
#define NMTOOLS_ARRAY_ARRAY_TANH_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct tanh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto tanh = view::tanh(a);
                return eval(tanh
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // tanh
    } // namespace fn

    constexpr inline auto tanh = fn::tanh{};
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_TANH_HPP