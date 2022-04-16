#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/expm1.hpp"

namespace nmtools::functional
{
    constexpr inline auto expm1 = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::expm1(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP