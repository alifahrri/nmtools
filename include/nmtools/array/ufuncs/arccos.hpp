#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arccos
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::acos(t);
        } // operator()
    }; // arccos
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arccos_t = fun::arccos;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arccos(const left_t& a)
    {
        return unary_ufunc(arccos_t{},a);
    } // arccos
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arccos,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arccos) const
        {
            nmtools_string str;

            str += "arccos";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCCOS_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/arccos.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arccos = fun::unary_ufunc<view::arccos_t>;
    }

    constexpr inline auto arccos = functor_t{unary_fmap_t<fun::arccos>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ARCCOS_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCCOS_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/arccos.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    template <
        typename output_t=none_t
        , typename context_t=default_context_t<>
        , typename array_t
        , enable_if_t<is_ndarray_v<array_t> || is_num_v<array_t> || (is_maybe_v<array_t> && (is_ndarray_v<array_t> || is_num_v<array_t>)),int> =0>
    constexpr auto arccos(const array_t& a,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto arccos = view::arccos(a);
        return eval(arccos
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // arccos
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ARCCOS_HPP