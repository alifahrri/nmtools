#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/tan.hpp"

namespace nmtools::functional
{
    constexpr inline auto tan = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::tan(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP