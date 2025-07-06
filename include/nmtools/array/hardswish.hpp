#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for hardswish ufunc.
     * 
     */
    struct hardswish
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            if (x < -3) {
                return static_cast<T>(0);
            } else if (x >= 3) {
                return x;
            } else {
                return x * (x + 3) / 6;
            }
        } // operator()
    }; // hardswish
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::hardswish
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::hardswish) const
        {
            nmtools_string str;

            str += "hardswish";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using hardswish_t = fun::hardswish;

    /**
     * @brief Create element-wise hardswish ufunc view.
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto hardswish(const array_t& array)
    {
        return ufunc(hardswish_t{},array);
    } // hardswish
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/hardswish.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using hardswish = fun::unary_ufunc<view::hardswish_t>;
    }

    constexpr inline auto hardswish = functor_t{unary_fmap_t<fun::hardswish>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/array/hardswish.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute element-wise hardswish ufunc.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto hardswish(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::hardswish(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // hardswish
} // namespace nmtools


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSWISH_HPP