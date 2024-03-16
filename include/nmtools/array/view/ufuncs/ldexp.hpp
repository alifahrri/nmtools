#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct ldexp
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::ldexp(t,u);
        } // operator()
    }; // ldexp
}
namespace nmtools::view
{
    using ldexp_t = fun::ldexp;

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto ldexp(const left_t& a, const right_t& b)
    {
        return ufunc(ldexp_t{},a,b);
    } // ldexp
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<view::fun::ldexp,none_t>
    {
        auto operator()(view::fun::ldexp) const
        {
            auto str = nmtools_string();

            str += "ldexp";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LDEXP_HPP