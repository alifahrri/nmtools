#ifndef NMTOOLS_ARRAY_FUNCTIONAL_WHERE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_WHERE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/where.hpp"

namespace nmtools::functional
{
    constexpr inline auto where = functor_t(ternary_fmap_t{
        [](const auto&...args){
            return view::where(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_WHERE_HPP