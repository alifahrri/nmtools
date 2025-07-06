#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP

#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for prelu ufunc
     * 
     * @tparam alpha_t 
     */
    template <typename alpha_t=float>
    struct prelu
    {
        const alpha_t alpha = 0.25;

        template <typename T>
        constexpr auto operator()(const T& t) const -> T
        {
            if (t >= 0) {
                return t;
            } else {
                return alpha * t;
            }
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& t) const noexcept
        {
            return prelu<T>{nmtools::get<0>(t)};
        }

        template <typename T>
        constexpr auto operator==(const prelu<T> other) const
        {
            return utils::isclose(alpha,other.alpha);
        }
    }; // prelu
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename alpha_t, auto...fmt_args>
    struct to_string_t<view::fun::prelu<alpha_t>,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::prelu<alpha_t> op) const
        {
            nmtools_string str;

            str += "prelu";
            str += "{";
            str += ".alpha=";
            str += to_string(op.alpha);
            str += "}";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename alpha_t=float>
    using prelu_t = fun::prelu<alpha_t>;

    /**
     * @brief Create element-wise prelu ufunc view
     * 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha 
     * @return constexpr auto 
     */
    template <typename array_t, typename alpha_t=float>
    constexpr auto prelu(const array_t& array, alpha_t alpha=alpha_t{0.25})
    {
        return ufunc(prelu_t<alpha_t>{{alpha}},array);
    } // prelu

    template <typename array_t, typename alpha_t=float>
    constexpr auto prelu(const array_t& array, fun::prelu<alpha_t> op)
    {
        return ufunc(op,array);
    } // prelu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/prelu.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using prelu = fun::unary_ufunc<view::prelu_t<>>;
    }
    constexpr inline auto prelu = functor_t{unary_fmap_t<fun::prelu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_PRELU_HPP

#include "nmtools/array/prelu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate element-wise prelu
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     negative slope of prelu
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename alpha_t=float>
    constexpr auto prelu(const array_t& array, alpha_t alpha=alpha_t{0.25},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::prelu(array,alpha);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // prelu
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_PRELU_HPP