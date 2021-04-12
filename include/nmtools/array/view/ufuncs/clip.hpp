#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CLIP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CLIP_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct clip_t
    {
        template <typename T, typename min_t, typename max_t>
        constexpr auto operator()(const T& t, const min_t& min, const max_t& max) const
        {
            auto r = t < min ? min : t;
                 r = r > max ? max : r;
            return r;
        } // operator()
    }; // clip_t

    template <typename array_t, typename amin_t, typename amax_t>
    constexpr auto clip(const array_t& array, const amin_t& amin, const amax_t& amax)
    {
        return ufunc(clip_t{},array,amin,amax);
    } // clip
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CLIP_HPP