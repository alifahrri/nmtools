#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arccosh.hpp"

namespace nmtools::functional
{
    constexpr inline auto arccosh = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::arccosh(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP