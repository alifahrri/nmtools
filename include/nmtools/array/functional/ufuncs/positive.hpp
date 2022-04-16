#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/positive.hpp"

namespace nmtools::functional
{
    constexpr inline auto positive = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::positive(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP