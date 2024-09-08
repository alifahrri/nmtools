#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_CELU_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
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