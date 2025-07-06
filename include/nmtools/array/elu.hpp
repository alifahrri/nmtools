#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for ELU ufunc.
     * 
     * @tparam alpha_t 
     */
    template <typename alpha_t=float>
    struct elu
    {
        const alpha_t alpha = 1.0;

        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return (t > 0? t : alpha * (math::exp(t)-1));
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& t) const noexcept
        {
            return elu<T>{nmtools::get<0>(t)};
        }

        template <typename T>
        constexpr auto operator==(const elu<T> other) const
        {
            return utils::isclose(alpha,other.alpha);
        }
    }; // elu
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename alpha_t
        , auto...fmt_args
    >
    struct to_string_t<view::fun::elu<alpha_t>
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::elu<alpha_t> op) const noexcept
        {
            nmtools_string str;
            str += "elu";
            str += "{";
            str += ".alpha=";
            str += to_string(op.alpha);
            str += "}";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename alpha_t=float>
    using elu_t = fun::elu<alpha_t>;

    /**
     * @brief Create element-wise ELU ufunc view.
     * 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     the alpha value of ELU formulation.
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t, typename alpha_t=float>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto elu(const array_t& array, alpha_t alpha=alpha_t{1})
    {
        return ufunc(elu_t<alpha_t>{{alpha}}, array);
    } // elu

    template <typename array_t, typename alpha_t=float>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto elu(const array_t& array, fun::elu<alpha_t> op)
    {
        return ufunc(op,array);
    }
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/elu.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using elu = fun::unary_ufunc<view::elu_t<>>;
    }

    constexpr inline auto elu = functor_t{unary_fmap_t<fun::elu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_ELU_HPP

#include "nmtools/array/elu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute element-wise elu function.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam alpha_t 
     * @param array     input array
     * @param alpha     the alpha value in elu formulation
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename alpha_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto elu(const array_t& array, alpha_t alpha=alpha_t{1.0},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::elu(array,alpha);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // elu
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_ELU_HPP