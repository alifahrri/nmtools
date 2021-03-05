#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct logical_xor_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return static_cast<bool>(t) ^ static_cast<bool>(u);
        } // operator()
    }; // logical_xor_t

    template <typename left_t, typename right_t>
    constexpr auto logical_xor(const left_t& a, const right_t& b)
    {
        return ufunc(logical_xor_t{},a,b);
    } // logical_xor
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOGICAL_XOR_HPP