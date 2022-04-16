#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/flip.hpp"

namespace nmtools::functional
{
    constexpr inline auto flip = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::flip(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP