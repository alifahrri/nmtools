#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/rint.hpp"

namespace nmtools::functional
{
    constexpr inline auto rint = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::rint(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP