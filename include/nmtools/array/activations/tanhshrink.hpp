#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for tanhshrink ufunc
     * 
     */
    struct tanhshrink
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        nmtools_func_attribute
        auto operator()(const T& x) const
        {
            return x - math::tanh(x);
        } // operator()
    }; // tanhshrink
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::tanhshrink,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::tanhshrink) const
        {
            nmtools_string str;

            str += "tanhshrink";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using tanhshrink_t = fun::tanhshrink;

    /**
     * @brief Create element-wise tanhshrink ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tanhshrink(const array_t& array)
    {
        return ufunc(tanhshrink_t{},array);
    } // tanhshrink
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/tanhshrink.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using tanhshrink = fun::unary_ufunc<view::tanhshrink_t>;
    }

    constexpr inline auto tanhshrink = functor_t{unary_fmap_t<fun::tanhshrink>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/array/activations/tanhshrink.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise tanhshrink function
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto tanhshrink(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::tanhshrink(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // tanhshrink
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_TANHSHRINK_HPP