#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for log sigmoid ufunc.
     * 
     */
    struct log_sigmoid
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            auto one = static_cast<T>(1);
            return math::log(one / (one + math::exp(-t)));
        } // operator()
    }; // log_sigmoid
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log_sigmoid
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::log_sigmoid) const
        {
            nmtools_string str;

            str += "log_sigmoid";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using log_sigmoid_t = fun::log_sigmoid;

    /**
     * @brief Create element-wise log sigmoid ufunc view.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return  
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log_sigmoid(const array_t& array)
    {
        return ufunc(log_sigmoid_t{}, array);
    } // log_sigmoid
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LOG_SIGMOID_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/log_sigmoid.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log_sigmoid = fun::unary_ufunc<view::log_sigmoid_t>;
    }
    constexpr inline auto log_sigmoid = functor_t{unary_fmap_t<fun::log_sigmoid>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/array/log_sigmoid.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute element-wise log sigmoid
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
    auto log_sigmoid(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::log_sigmoid(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // log_sigmoid
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_LOG_SIGMOID_HPP