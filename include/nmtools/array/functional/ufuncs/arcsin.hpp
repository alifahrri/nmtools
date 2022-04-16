#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arcsin.hpp"

namespace nmtools::functional
{
    constexpr inline auto arcsin = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::arcsin(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP