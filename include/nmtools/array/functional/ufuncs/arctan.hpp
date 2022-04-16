#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctan.hpp"

namespace nmtools::functional
{
    constexpr inline auto arctan = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::arctan(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP