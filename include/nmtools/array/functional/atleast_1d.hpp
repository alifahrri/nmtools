#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_1D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_1D_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/atleast_1d.hpp"

namespace nmtools::functional
{
    constexpr inline auto atleast_1d = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::atleast_1d(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_1D_HPP