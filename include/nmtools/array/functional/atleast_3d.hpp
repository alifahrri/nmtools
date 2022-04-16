#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_3D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_3D_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/atleast_3d.hpp"

namespace nmtools::functional
{
    constexpr inline auto atleast_3d = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::atleast_3d(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_3D_HPP