#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arcsinh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::asinh(t);
        } // operator()
    }; // arcsinh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arcsinh_t = fun::arcsinh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arcsinh(const left_t& a)
    {
        return unary_ufunc(arcsinh_t{},a);
    } // arcsinh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arcsinh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arcsinh) const
        {
            nmtools_string str;

            str += "arcsinh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING


#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCSINH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/arcsinh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arcsinh = fun::unary_ufunc<view::arcsinh_t>;
    }

    constexpr inline auto arcsinh = functor_t{unary_fmap_t<fun::arcsinh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ARCSINH_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCSINH_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/arcsinh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    template <
        typename output_t=none_t
        , typename context_t=default_context_t<>
        , typename array_t
        , enable_if_t<is_ndarray_v<array_t> || is_num_v<array_t> || (is_maybe_v<array_t> && (is_ndarray_v<array_t> || is_num_v<array_t>)),int> =0>
    constexpr auto arcsinh(const array_t& a,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto arcsinh = view::arcsinh(a);
        return eval(arcsinh
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // arcsinh
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ARCSINH_HPP