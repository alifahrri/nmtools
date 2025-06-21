#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SELU_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for selu ufunc
     * 
     */
    struct selu
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            constexpr auto alpha = static_cast<T>(1.6732632423543772848170429916717);
            constexpr auto scale = static_cast<T>(1.0507009873554804934193349852946);
            constexpr auto zero  = static_cast<T>(0);
            return scale * (math::max(t,zero) + math::min(alpha * (math::exp(t) - 1), zero));
        } // operator()
    }; // selu
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::selu,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::selu) const
        {
            nmtools_string str;

            str += "selu";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using selu_t = fun::selu;

    /**
     * @brief Create element-wise selu ufunc view.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto selu(const array_t& array)
    {
        return ufunc(selu_t{},array);
    } // selu
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SELU_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/selu.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using selu = fun::unary_ufunc<view::selu_t>;
    }
    constexpr inline auto selu = functor_t{unary_fmap_t<fun::selu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SELU_HPP

#include "nmtools/array/activations/selu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate selu.
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
    auto selu(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::selu(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    }
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SELU_HPP