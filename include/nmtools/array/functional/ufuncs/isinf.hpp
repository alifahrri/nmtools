#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/isinf.hpp"

namespace nmtools::functional
{
    constexpr inline auto isinf = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::isinf(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP