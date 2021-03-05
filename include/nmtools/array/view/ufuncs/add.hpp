#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ADD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ADD_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct add_t
    {
        constexpr add_t() {}

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t + u;
        } // operator()
    }; // add_t

    template <typename left_t, typename right_t>
    constexpr auto add(const left_t& a, const right_t& b)
    {
        return ufunc(add_t{},a,b);
    } // add
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ADD_HPP