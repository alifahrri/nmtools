#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for ufunc relu view
     * 
     */
    struct relu
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            return static_cast<T>(x > 0? x : 0);
        } // operator()
    }; // relu   
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::relu,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::relu) const
        {
            nmtools_string str;

            str += "relu";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using relu_t = fun::relu;

    /**
     * @brief Creates element-wise ufunc relu view
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto relu(const array_t& array)
    {
        return ufunc(relu_t{},array);
    } // relu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using relu = fun::unary_ufunc<view::relu_t>;
    } // namespace fun

    constexpr inline auto relu = functor_t{unary_fmap_t<fun::relu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU_HPP

#include "nmtools/array/activations/relu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise relu.
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
    constexpr auto relu(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::relu(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // relu
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU_HPP