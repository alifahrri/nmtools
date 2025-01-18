#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP

#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for hardshrink ufunc.
     * 
     * @tparam lambda_t 
     */
    template <typename lambda_t=float>
    struct hardshrink
    {
        const lambda_t lambda = 0.5;

        template <typename T>
        constexpr auto operator()(const T& t) const -> T
        {
            auto x = t;
            if ((x >= -lambda) && (x <= lambda)) {
                x = 0;
            }
            return x;
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& t) const noexcept
        {
            return hardshrink<T>{nmtools::get<0>(t)};
        }

        template <typename T>
        constexpr auto operator==(const hardshrink<T> other) const
        {
            return utils::isclose(lambda,other.lambda);
        }
    }; // hardshrink
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename lambda_t
        , auto...fmt_args
    >
    struct to_string_t<view::fun::hardshrink<lambda_t>
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::hardshrink<lambda_t> op) const
        {
            nmtools_string str;

            str += "hardshrink";
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
    using hardshrink_t = fun::hardshrink<lambda_t>;

    /**
     * @brief Creates element-wise hardshrink ufunc view.
     * 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array 
     * @param lambda 
     * @return constexpr auto 
     */
    template <typename array_t, typename lambda_t=float>
    constexpr auto hardshrink(const array_t& array, lambda_t lambda=lambda_t{0.5})
    {
        return ufunc(hardshrink_t<lambda_t>{{lambda}},array);
    } // hardshrink

    template <typename array_t, typename lambda_t=float>
    constexpr auto hardshrink(const array_t& array, fun::hardshrink<lambda_t> op)
    {
        return ufunc(op,array);
    } // hardshrink
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/hardshrink.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using hardshrink = fun::unary_ufunc<view::hardshrink_t<>>;
    }

    constexpr inline auto hardshrink = functor_t{unary_fmap_t<fun::hardshrink>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSHRINK_HPP

#include "nmtools/array/activations/hardshrink.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise hardshrink function.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array     input array
     * @param lambda     the lambda value in hardshrink formulation
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename lambda_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto hardshrink(const array_t& array, lambda_t lambda=lambda_t{0.5},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::hardshrink(array,lambda);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // hardshrink
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSHRINK_HPP