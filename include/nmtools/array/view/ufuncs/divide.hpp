#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct divide_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t / u;
        } // operator()
    }; // divide_t

    template <typename left_t, typename right_t>
    constexpr auto divide(const left_t& a, const right_t& b)
    {
        return ufunc(divide_t{},a,b);
    } // divide
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP