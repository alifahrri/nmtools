#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sin.hpp"

namespace nmtools::functional
{
    constexpr inline auto sin = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::sin(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP