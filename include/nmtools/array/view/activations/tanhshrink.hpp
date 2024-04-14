#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for tanhshrink ufunc
     * 
     */
    struct tanhshrink
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        nmtools_func_attribute
        auto operator()(const T& x) const
        {
            return x - math::tanh(x);
        } // operator()
    }; // tanhshrink
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::tanhshrink,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::tanhshrink) const
        {
            nmtools_string str;

            str += "tanhshrink";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using tanhshrink_t = fun::tanhshrink;

    /**
     * @brief Create element-wise tanhshrink ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tanhshrink(const array_t& array)
    {
        return ufunc(tanhshrink_t{},array);
    } // tanhshrink
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP