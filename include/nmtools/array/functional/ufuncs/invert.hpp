#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/invert.hpp"

namespace nmtools::functional
{
    constexpr inline auto invert = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::invert(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP