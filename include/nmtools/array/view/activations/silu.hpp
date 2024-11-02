#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/activations/sigmoid.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for silu ufunc
     * 
     */
    struct silu : sigmoid
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return t * sigmoid::eval(t);
        } // operator()
    }; // silu
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::silu,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::silu) const
        {
            nmtools_string str;

            str += "silu";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using silu_t = fun::silu;

    /**
     * @brief Create element-wise Sigmoid Linear Unit (SiLU) ufunc view.
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto silu(const array_t& array)
    {
        return ufunc(silu_t{},array);
    } // silu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SILU_HPP