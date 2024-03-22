#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_ELU_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
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
    template <typename alpha_t>
    struct to_string_t<view::fun::elu<alpha_t>,none_t>
    {
        auto operator()(view::fun::elu<alpha_t> op) const noexcept
        {
            nmtools_string str;
            str += "elu{.alpha=";
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