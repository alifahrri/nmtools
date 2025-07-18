#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LEAKY_RELU_HPP

#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for leaky relu ufunc
     * 
     * @tparam negative_slope_t 
     */
    template <typename negative_slope_t=float>
    struct leaky_relu
    {
        const negative_slope_t negative_slope = 0.01;

        template <typename T>
        constexpr auto operator()(const T& t) const -> T
        {
            return (t >= 0? t : negative_slope * t);
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& t) const noexcept
        {
            return leaky_relu<T>{nmtools::get<0>(t)};
        }

        template <typename T>
        constexpr auto operator==(const leaky_relu<T> other) const
        {
            return utils::isclose(negative_slope,other.negative_slope);
        }
    }; // leaky_relu
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename negative_slope_t
        , auto...fmt_args
    >
    struct to_string_t<view::fun::leaky_relu<negative_slope_t>
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::leaky_relu<negative_slope_t> op) const
        {
            nmtools_string str;

            str += "leaky_relu";
            str += "{";
            str += ".negative_slope=";
            str += to_string(op.negative_slope);
            str += "}";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename negative_slope_t=float>
    using leaky_relu_t = fun::leaky_relu<negative_slope_t>;

    /**
     * @brief Create element-wise leaky relu ufunc view.
     * 
     * @tparam array_t 
     * @tparam negative_slope_t 
     * @param array             input array
     * @param negative_slope    controls the angle of the negative slope
     * @return constexpr auto 
     */
    template <typename array_t, typename negative_slope_t=float>
    constexpr auto leaky_relu(const array_t& array, negative_slope_t negative_slope=negative_slope_t{0.01})
    {
        return ufunc(leaky_relu_t<negative_slope_t>{{negative_slope}},array);
    } // leaky_relu

    template <typename array_t, typename negative_slope_t=float>
    constexpr auto leaky_relu(const array_t& array, fun::leaky_relu<negative_slope_t> op)
    {
        return ufunc(op,array);
    } // leaky_relu
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_LEAKY_RELU_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/leaky_relu.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using leaky_relu = fun::unary_ufunc<view::leaky_relu_t<>>;
    }
    constexpr inline auto leaky_relu = functor_t{unary_fmap_t<fun::leaky_relu>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATION_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATION_LEAKY_RELU_HPP

#include "nmtools/array/leaky_relu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute element-wise leaky relu
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam negative_slope_t 
     * @param array             input array
     * @param negative_slope    controls the angle of the negative slope
     * @param context           evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename negative_slope_t=float>
    constexpr auto leaky_relu(const array_t& array, negative_slope_t negative_slope=negative_slope_t{0.01},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::leaky_relu(array,negative_slope);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // leaky_relu
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATION_LEAKY_RELU_HPP