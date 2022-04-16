#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/atleast_2d.hpp"

namespace nmtools::functional
{
    constexpr inline auto atleast_2d = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::atleast_2d(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP