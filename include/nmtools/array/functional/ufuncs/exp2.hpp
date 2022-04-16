#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/exp2.hpp"

namespace nmtools::functional
{
    constexpr inline auto exp2 = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::exp2(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP