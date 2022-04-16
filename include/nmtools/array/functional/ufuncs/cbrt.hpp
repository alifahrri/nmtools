#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cbrt.hpp"

namespace nmtools::functional
{
    constexpr inline auto cbrt = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::cbrt(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP