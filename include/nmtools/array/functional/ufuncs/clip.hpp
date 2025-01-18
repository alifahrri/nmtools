#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/clip.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct clip_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::clip(args...);
            }
        };
    }

    constexpr inline auto clip = functor_t{ternary_fmap_t<fun::clip_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP