#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP

#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/activations/softplus.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for mish ufunc
     * 
     */
    struct mish
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return t * math::tanh(softplus<>::eval(t));
        } // operator()
    }; // mish
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::mish,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::mish) const
        {
            nmtools_string str;

            str += "mish";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using mish_t = fun::mish;

    /**
     * @brief Create element-wise mish ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto mish(const array_t& array)
    {
        return ufunc(mish_t{},array);
    } // mish
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP