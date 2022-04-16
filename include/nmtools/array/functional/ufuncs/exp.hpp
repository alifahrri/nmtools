#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/exp.hpp"

namespace nmtools::functional
{
    constexpr inline auto exp = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::exp(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP