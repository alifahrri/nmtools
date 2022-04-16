#ifndef NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/broadcast_to.hpp"

namespace nmtools::functional
{
    constexpr inline auto broadcast_to = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::broadcast_to(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP