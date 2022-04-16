#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arccos.hpp"

namespace nmtools::functional
{
    constexpr inline auto arccos = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::arccos(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP