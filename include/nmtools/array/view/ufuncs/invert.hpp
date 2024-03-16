#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::meta::error
{
    template <typename...>
    struct INVERT_UNSUPPORTED : detail::fail_t {};
}

namespace nmtools::view::fun
{
    struct invert
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            if constexpr (meta::expression_check_v<meta::expr::invert,T>) {
                return ~t;
            } else {
                return meta::error::INVERT_UNSUPPORTED<T>{};
            }
        } // operator()
    }; // invert   
} // namespace nmtools::view::fun

namespace nmtools::view
{
    using invert_t = fun::invert;
    template <typename left_t>
    constexpr auto invert(const left_t& a)
    {
        return ufunc(invert_t{},a);
    } // invert
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::invert,none_t>
    {
        auto operator()(view::fun::invert) const
        {
            nmtools_string str;

            str += "invert";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_INVERT_HPP