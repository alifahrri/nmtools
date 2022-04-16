#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/isfinite.hpp"

namespace nmtools::functional
{
    constexpr inline auto isfinite = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::isfinite(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP