#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cosh.hpp"

namespace nmtools::functional
{
    constexpr inline auto cosh = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::cosh(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP