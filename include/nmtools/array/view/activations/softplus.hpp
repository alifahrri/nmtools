#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTPLUS_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTPLUS_HPP

#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for softplus ufunc
     * 
     * @tparam beta_t 
     * @tparam threshold_t 
     */
    template <typename beta_t=float, typename threshold_t=beta_t>
    struct softplus
    {
        const beta_t beta = 1;
        const threshold_t threshold = 20;

        template <typename beta_type=float, typename threshold_type=float, typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        static auto eval(const T& x, beta_type beta=beta_type{1}, threshold_type threshold=threshold_type{20})
        {
            using result_t = decltype(math::exp(x));
            result_t res = x;
            auto t_times_beta = res * beta;
            if (t_times_beta > threshold) {
                return res;
            } else {
                return static_cast<result_t>(math::log(1 + math::exp(t_times_beta)) / beta);
            }
        } // eval

        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& x) const
        {
            return eval(x,beta,threshold);
        } // operator()

        template <template<typename...>typename tuple, typename T, typename U>
        constexpr auto operator[](const tuple<T,U>& x) const noexcept
        {
            return softplus<T,U>{nmtools::get<0>(x),nmtools::get<1>(x)};
        }

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& x) const noexcept
        {
            return softplus<T>{nmtools::get<0>(x)};
        }

        template <typename T>
        constexpr auto operator==(const softplus<T> other) const
        {
            return utils::isclose(beta,other.beta)
                && utils::isclose(threshold,other.threshold);
        }
    }; // softplus
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename beta_t, typename threshold_t, auto...fmt_args>
    struct to_string_t<view::fun::softplus<beta_t,threshold_t>,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::softplus<beta_t,threshold_t> op) const
        {
            nmtools_string str;

            str += "softplus";
            str += "{";
            str += ".beta=";
            str += to_string(op.beta);
            str += ",.threshold=";
            str += to_string(op.threshold);
            str += "}";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename beta_t=float, typename threshold_t=float>
    using softplus_t = fun::softplus<beta_t,threshold_t>;

    /**
     * @brief Create element-wise softplus ufunc view.
     * 
     * @tparam array_t 
     * @tparam beta_t 
     * @tparam threshold_t 
     * @param array     input array
     * @param beta      the beta value of softplus formulation
     * @param threshold values above this revert to linear function
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t, typename beta_t=float, typename threshold_t=float>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto softplus(const array_t& array, beta_t beta=beta_t{1}, threshold_t threshold=threshold_t{20})
    {
        return ufunc(softplus_t<beta_t,threshold_t>{beta,threshold},array);
    } // softplus

    template <typename array_t, typename beta_t=float, typename threshold_t=float>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto softplus(const array_t& array, fun::softplus<beta_t,threshold_t> op)
    {
        return ufunc(op,array);
    } // softplus
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTPLUS_HPP