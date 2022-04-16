#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arcsinh.hpp"

namespace nmtools::functional
{
    constexpr inline auto arcsinh = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::arcsinh(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP