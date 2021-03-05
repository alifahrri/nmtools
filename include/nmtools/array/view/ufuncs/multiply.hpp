#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MULTIPLY_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MULTIPLY_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct multiply_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t * u;
        } // operator()
    }; // multiply_t

    template <typename left_t, typename right_t>
    constexpr auto multiply(const left_t& a, const right_t& b)
    {
        return ufunc(multiply_t{},a,b);
    } // multiply
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MULTIPLY_HPP