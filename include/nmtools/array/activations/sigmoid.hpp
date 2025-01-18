#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for sigmoid ufunc
     * 
     */
    struct sigmoid
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        static auto eval(const T& t)
        {
            auto one = static_cast<T>(1);
            return one / (one + math::exp(-t));
        } // sigmoid

        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return eval(t);
        } // operator()
    }; // sigmoid
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::sigmoid,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::sigmoid) const
        {
            nmtools_string str;

            str += "sigmoid";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using sigmoid_t = fun::sigmoid;

    /**
     * @brief Create element-wise sigmoid ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sigmoid(const array_t& array)
    {
        return ufunc(sigmoid_t{},array);
    } // sigmoid
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/sigmoid.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using sigmoid = fun::unary_ufunc<view::sigmoid_t>;
    }
    constexpr inline auto sigmoid = functor_t{unary_fmap_t<fun::sigmoid>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/array/activations/sigmoid.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise sigmoid function.
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
    auto sigmoid(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::sigmoid(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // sigmoid
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SIGMOID_HPP