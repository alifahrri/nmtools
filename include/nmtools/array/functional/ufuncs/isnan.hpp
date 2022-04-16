#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/isnan.hpp"

namespace nmtools::functional
{
    constexpr inline auto isnan = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::isnan(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP