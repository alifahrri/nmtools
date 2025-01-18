#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/tile.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct tile_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::tile(args...);
            }
        };
    }

    constexpr inline auto tile = functor_t{unary_fmap_t<fun::tile_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP