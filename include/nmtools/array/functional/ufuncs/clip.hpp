#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/clip.hpp"

namespace nmtools::functional
{
    constexpr inline auto clip = functor_t(ternary_fmap_t{
        [](const auto&...args){
            return view::clip(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP