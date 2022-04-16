#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log1p.hpp"

namespace nmtools::functional
{
    constexpr inline auto log1p = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::log1p(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP