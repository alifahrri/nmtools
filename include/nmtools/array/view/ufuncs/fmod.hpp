#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP

#include "nmtools/array/view/ufunc.hpp"

#include <cmath>

namespace nmtools::view
{
    struct fmod_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return std::fmod(t,u);
        } // operator()
    }; // fmod_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmod(const left_t& a, const right_t& b)
    {
        return ufunc(fmod_t{},a,b);
    } // fmod
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP