#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/flatten.hpp"

namespace nmtools::functional
{
    constexpr inline auto flatten = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::flatten(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP