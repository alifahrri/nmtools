#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sinh.hpp"

namespace nmtools::functional
{
    constexpr inline auto sinh = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::sinh(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP