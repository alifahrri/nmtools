#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/tile.hpp"

namespace nmtools::functional
{
    constexpr inline auto tile = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::tile(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP