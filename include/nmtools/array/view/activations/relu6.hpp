#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct relu6
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            auto x = t;
            if (x < 0) {
                x = 0;
            } else if (x > 6) {
                x = 6;
            }
            return x;
        } // operator()
    }; // relu6
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::relu6,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::relu6) const
        {
            nmtools_string str;

            str += "relu6";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using relu6_t = fun::relu6;

    template <typename array_t>
    constexpr auto relu6(const array_t& array)
    {
        return ufunc(relu6_t{},array);
    } // relu6
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP