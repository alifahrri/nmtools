#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/fabs.hpp"

namespace nmtools::functional
{
    constexpr inline auto fabs = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::fabs(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP