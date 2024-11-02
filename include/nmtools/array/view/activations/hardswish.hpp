#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for hardswish ufunc.
     * 
     */
    struct hardswish
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            if (x < -3) {
                return static_cast<T>(0);
            } else if (x >= 3) {
                return x;
            } else {
                return x * (x + 3) / 6;
            }
        } // operator()
    }; // hardswish
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::hardswish
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::hardswish) const
        {
            nmtools_string str;

            str += "hardswish";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using hardswish_t = fun::hardswish;

    /**
     * @brief Create element-wise hardswish ufunc view.
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto hardswish(const array_t& array)
    {
        return ufunc(hardswish_t{},array);
    } // hardswish
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDSWISH_HPP