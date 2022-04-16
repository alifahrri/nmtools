#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/negative.hpp"

namespace nmtools::functional
{
    constexpr inline auto negative = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::negative(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP