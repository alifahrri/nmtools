#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct tan
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::tan(t);
        } // operator()
    }; // tan
}

namespace nmtools::view
{
    using tan_t = fun::tan;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tan(const left_t& a)
    {
        return unary_ufunc(tan_t{},a);
    } // tan
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::tan,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::tan) const
        {
            nmtools_string str;

            str += "tan";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_TAN_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/tan.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using tan = fun::unary_ufunc<view::tan_t>;
    }

    constexpr inline auto tan = functor_t{unary_fmap_t<fun::tan>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TAN_HPP
#define NMTOOLS_ARRAY_ARRAY_TAN_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/tan.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    template <
        typename output_t=none_t
        , typename context_t=default_context_t<>
        , typename array_t
        , enable_if_t<is_ndarray_v<array_t> || is_num_v<array_t> || (is_maybe_v<array_t> && (is_ndarray_v<array_t> || is_num_v<array_t>)),int> =0>
    constexpr auto tan(const array_t& a,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto tan = view::tan(a);
        return eval(tan
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // tan
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_TAN_HPP