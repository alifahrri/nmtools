#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/floor.hpp"

namespace nmtools::functional
{
    constexpr inline auto floor = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::floor(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP