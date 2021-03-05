#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct mod_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t % u;
        } // operator()
    }; // mod_t

    template <typename left_t, typename right_t>
    constexpr auto mod(const left_t& a, const right_t& b)
    {
        return ufunc(mod_t{},a,b);
    } // mod
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_MOD_HPP