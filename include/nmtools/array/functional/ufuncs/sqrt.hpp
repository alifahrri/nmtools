#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"

namespace nmtools::functional
{
    constexpr inline auto sqrt = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::sqrt(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP