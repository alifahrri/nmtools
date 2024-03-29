#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view::fun
{
    struct square
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            return t * t;
        } // operator()
    }; // square
}

namespace nmtools::view
{
    using square_t = fun::square;

    template <typename left_t>
    constexpr auto square(const left_t& a)
    {
        return ufunc(square_t{},a);
    } // square
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::square,none_t>
    {
        auto operator()(view::fun::square) const
        {
            nmtools_string str;

            str += "square";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_SQUARE_HPP