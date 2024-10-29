#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for ufunc relu view
     * 
     */
    struct relu
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            return static_cast<T>(x > 0? x : 0);
        } // operator()
    }; // relu   
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::relu,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::relu) const
        {
            nmtools_string str;

            str += "relu";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using relu_t = fun::relu;

    /**
     * @brief Creates element-wise ufunc relu view
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto relu(const array_t& array)
    {
        return ufunc(relu_t{},array);
    } // relu
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU_HPP