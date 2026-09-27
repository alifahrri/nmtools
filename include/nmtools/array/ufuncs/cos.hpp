#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct cos
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::cos(t);
        } // operator()
    }; // cos
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using cos_t = fun::cos;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto cos(const left_t& a)
    {
        return unary_ufunc(cos_t{},a);
    } // cos
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::cos,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::cos) const
        {
            nmtools_string str;

            str += "cos";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_COS_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using cos = fun::unary_ufunc<view::cos_t>;
    }

    constexpr inline auto cos = functor_t{unary_fmap_t<fun::cos>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_COS_HPP
#define NMTOOLS_ARRAY_ARRAY_COS_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    template <
        typename output_t=none_t
        , typename context_t=default_context_t<>
        , typename array_t
        , enable_if_t<is_ndarray_v<array_t> || is_num_v<array_t> || (is_maybe_v<array_t> && (is_ndarray_v<array_t> || is_num_v<array_t>)),int> =0>
    constexpr auto cos(const array_t& a,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto cos = view::cos(a);
        return eval(cos
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // cos
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_COS_HPP