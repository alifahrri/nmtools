#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for ufunc celu view.
     * 
     * @tparam alpha_t 
     */
    template <typename alpha_t=float>
    struct celu
    {
        const alpha_t alpha = 1.0;

        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            constexpr auto zero = static_cast<T>(0);
            return math::max(zero,t) + math::min(zero,alpha*(math::exp(t / alpha)-1));
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& t) const noexcept
        {
            return celu<T>{nmtools::get<0>(t)};
        }

        template <typename T>
        constexpr auto operator==(const celu<T> other) const
        {
            return utils::isclose(alpha,other.alpha);
        }
    }; // celu
} // namespace nmtools::view::fun

namespace nmtools::view
{
    template <typename alpha_t=float>
    using celu_t = fun::celu<alpha_t>;

    /**
     * @brief Create element-wise celu ufunc view.
     * 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     the alpha value in the celu formulation.
     * @return 
     */
    template <typename array_t, typename alpha_t=float>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto celu(const array_t& array, alpha_t alpha=alpha_t{1.0})
    {
        return ufunc(celu_t<alpha_t>{{alpha}},array);
    } // celu

    template <typename array_t, typename alpha_t=float>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto celu(const array_t& array, fun::celu<alpha_t> op)
    {
        return ufunc(op,array);
    } // celu
} // namespace nmtools::view

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename alpha_t
        , auto...fmt_args
    >
    struct to_string_t<view::fun::celu<alpha_t>
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::celu<alpha_t> op) const
        {
            nmtools_string str;
            str += "celu";
            str += "{";
            str += ".alpha=";
            str += to_string(op.alpha);
            str += "}";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/celu.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using celu = fun::unary_ufunc<view::celu_t<>>;
    }

    // we want celu[alpha] to works, so do not use fun::unary_ufunc<view::celu_t<>>;
    constexpr inline auto celu = functor_t{unary_fmap_t<fun::celu>{}};

    // using lambda breaks boost type index: Type name demangling failed
    // constexpr inline auto celu = functor_t(unary_fmap_t<decltype(celu_fun)>{celu_fun});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_CELU_HPP

#include "nmtools/array/activations/celu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise celu function.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     the alpha value in celu formulation
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename alpha_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto celu(const array_t& array, alpha_t alpha=alpha_t{1.0},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::celu(array,alpha);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // celu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_CELU_HPP