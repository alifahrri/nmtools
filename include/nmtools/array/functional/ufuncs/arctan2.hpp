#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctan2.hpp"

namespace nmtools::functional
{
    constexpr inline auto arctan2 = functor_t(binary_fmap_t{
        [](const auto&...args){
            return view::arctan2(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP