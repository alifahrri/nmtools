#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SELU_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for selu ufunc
     * 
     */
    struct selu
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            constexpr auto alpha = static_cast<T>(1.6732632423543772848170429916717);
            constexpr auto scale = static_cast<T>(1.0507009873554804934193349852946);
            constexpr auto zero  = static_cast<T>(0);
            return scale * (math::max(t,zero) + math::min(alpha * (math::exp(t) - 1), zero));
        } // operator()
    }; // selu
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::selu,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::selu) const
        {
            nmtools_string str;

            str += "selu";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using selu_t = fun::selu;

    /**
     * @brief Create element-wise selu ufunc view.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto selu(const array_t& array)
    {
        return ufunc(selu_t{},array);
    } // selu
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SELU_HPP