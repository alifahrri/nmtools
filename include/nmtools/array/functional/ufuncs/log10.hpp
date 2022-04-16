#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log10.hpp"

namespace nmtools::functional
{
    constexpr inline auto log10 = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::log10(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP