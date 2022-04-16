#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/ceil.hpp"

namespace nmtools::functional
{
    constexpr inline auto ceil = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::ceil(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP