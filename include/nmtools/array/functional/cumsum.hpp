#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/cumsum.hpp"

namespace nmtools::functional
{
    constexpr inline auto cumsum = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::cumsum(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP