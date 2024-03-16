#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_PRELU_HPP

#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

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
    template <typename alpha_t>
    struct to_string_t<view::fun::prelu<alpha_t>,none_t>
    {
        auto operator()(view::fun::prelu<alpha_t> op) const
        {
            nmtools_string str;

            str += "prelu{.alpha=";
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