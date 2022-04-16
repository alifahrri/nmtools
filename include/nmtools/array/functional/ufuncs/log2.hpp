#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log2.hpp"

namespace nmtools::functional
{
    constexpr inline auto log2 = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::log2(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP