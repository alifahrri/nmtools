#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/reciprocal.hpp"

namespace nmtools::functional
{
    constexpr inline auto reciprocal = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::reciprocal(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP