#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arctanh
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::atanh(t);
        } // operator()
    }; // arctanh
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using arctanh_t = fun::arctanh;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctanh(const left_t& a)
    {
        return unary_ufunc(arctanh_t{},a);
    } // arctanh
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arctanh,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arctanh) const
        {
            nmtools_string str;

            str += "arctanh";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTANH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/arctanh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arctanh = fun::unary_ufunc<view::arctanh_t>;
    }

    constexpr inline auto arctanh = functor_t{unary_fmap_t<fun::arctanh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ARCTANH_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCTANH_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/arctanh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct arctanh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto arctanh = view::arctanh(a);
                return eval(arctanh
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // arctanh
    } // namespace fn

    constexpr inline auto arctanh = fn::arctanh{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ARCTANH_HPP