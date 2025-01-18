#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for sigmoid ufunc
     * 
     */
    struct sigmoid
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        static auto eval(const T& t)
        {
            auto one = static_cast<T>(1);
            return one / (one + math::exp(-t));
        } // sigmoid

        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return eval(t);
        } // operator()
    }; // sigmoid
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::sigmoid,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::sigmoid) const
        {
            nmtools_string str;

            str += "sigmoid";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using sigmoid_t = fun::sigmoid;

    /**
     * @brief Create element-wise sigmoid ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto sigmoid(const array_t& array)
    {
        return ufunc(sigmoid_t{},array);
    } // sigmoid
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SIGMOID_HPP