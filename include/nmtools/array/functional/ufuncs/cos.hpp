#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cos.hpp"

namespace nmtools::functional
{
    constexpr inline auto cos = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::cos(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP