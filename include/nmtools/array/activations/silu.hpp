#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/array/activations/sigmoid.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for silu ufunc
     * 
     */
    struct silu : sigmoid
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return t * sigmoid::eval(t);
        } // operator()
    }; // silu
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::silu,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::silu) const
        {
            nmtools_string str;

            str += "silu";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using silu_t = fun::silu;

    /**
     * @brief Create element-wise Sigmoid Linear Unit (SiLU) ufunc view.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto silu(const array_t& array)
    {
        return ufunc(silu_t{},array);
    } // silu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/silu.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using silu = fun::unary_ufunc<view::silu_t>;
    }

    constexpr inline auto silu = functor_t{unary_fmap_t<fun::silu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SILU_HPP

#include "nmtools/array/activations/silu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise silu function
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
    auto silu(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::silu(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // silu
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SILU_HPP