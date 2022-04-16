#ifndef NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/expand_dims.hpp"

namespace nmtools::functional
{
    constexpr inline auto expand_dims = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::expand_dims(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP