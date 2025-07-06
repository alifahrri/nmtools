#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/core/ufunc.hpp"
// TODO: maybe do not include all parts of isclose here, refactor to isclose_t maybe
#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for softshrink ufunc
     * 
     * @tparam lambda_t 
     */
    template <typename lambda_t=float>
    struct softshrink
    {
        const lambda_t lambda = 0.5;

        template <typename T>
        constexpr auto operator()(const T& x) const -> T
        {
            if (x > lambda) {
                return x - lambda;
            } else if (x < -lambda) {
                return x + lambda;
            } else {
                return static_cast<T>(0);
            }
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T> args) const noexcept
        {
            return softshrink<T>{nmtools::get<0>(args)};
        }

        template <typename T>
        constexpr auto operator==(const softshrink<T> other) const
        {
            return utils::isclose(lambda,other.lambda);
        }
    }; // softshrink
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename lambda_t, auto...fmt_args>
    struct to_string_t<view::fun::softshrink<lambda_t>,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::softshrink<lambda_t> op) const
        {
            nmtools_string str;

            str += "softshrink";
            str += "{";
            str += ".lambda=";
            str += to_string(op.lambda); 
            str += "}";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename lambda_t=float>
    using softshrink_t = fun::softshrink<lambda_t>;

    /**
     * @brief Create element-wise softshrink ufunc view.
     * 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array     input array
     * @param lambda    lambda value of softshrink formulation
     * @return constexpr auto 
     */
    template <typename array_t, typename lambda_t=float>
    constexpr auto softshrink(const array_t& array, lambda_t lambda=lambda_t{0.5})
    {
        return ufunc(softshrink_t<lambda_t>{{lambda}},array);
    } // softshrink

    template <typename array_t, typename lambda_t=float>
    constexpr auto softshrink(const array_t& array, fun::softshrink<lambda_t> op)
    {
        return ufunc(op,array);
    } // softshrink
    
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/softshrink.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using softshrink = fun::unary_ufunc<view::softshrink_t<>>;
    }
    constexpr inline auto softshrink = functor_t{unary_fmap_t<fun::softshrink>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/array/softshrink.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate element-wise softshrink function
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array     input array
     * @param lambda    lambda value of softshrink formulation
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename lambda_t=float>
    constexpr auto softshrink(const array_t& array, lambda_t lambda=lambda_t{0.5},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::softshrink(array,lambda);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softshrink
} // namespace nmtools


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSHRINK_HPP